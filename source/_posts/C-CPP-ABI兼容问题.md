---
title: 【C/C++】ABI兼容问题
tags:
  - C/C++
  - ABI
categories:
  - 技术
  - C/C++
  - 问题分析
date: 2026-07-27 15:16:12
updated: 2026-07-27 15:16:12
description: 介绍说明 C/C++ 开发中常见的 ABI 兼容问题的出现原因以及解决方案
keywords:
---

## 问题简述

- **ABI**（Application Binary Interface，应用程序二进制接口）：主要描述应用程序和操作系统之间，一个应用和它的库之间，或应用的组成部分之间的底层接口。
- **API**（Application Programming Interface，应用程序编程接口）：一组预定义的规则和协议，允许不同的软件应用程序相互通信和交互。

在说明 ABI 问题之前，先说明一下 API 问题，以免混淆。



### API 问题

通常来说，两个程序之间提供的接口，主调方在调用被调方提供的接口时需要遵循被调方的相关规则和协议，否则在程序运行过程中将会产生接口调用失败的相关情况。

对于单纯的 C/C++ 程序来说，直接通过类/函数接口调用时，如果不遵循 API 的规则，那么大概率该程序在编译阶段就会出错，故通常不会表现在程序运行阶段。



### ABI 问题

ABI 问题通常发生在可执行程序和动态库之间。

C/C++的语言标准中有许多的未定义行为以及不明确的语法，这些行为上具体的区别在使用不同的编译器之间会有一定的体现。例如`long`类型的默认宽度，`char`类型的默认符号性等这类基础的兼容问题；也有在 C++ 中引入的复杂的对象模型的不同实现方式造成的兼容问题。

当 ABI 问题发生时，程序可能会出现不按预期行为执行或崩溃等错误情况。



## 解决方案

### 使用 C 接口

将 C++ 库封装为 C 接口是最推荐的一个方案，其效果也比较好。只是由于该层封装，导致该库无法直接支持 C++ 的特性。

C++ 贴心的提供了这样的能力，大概头文件框架如下：

```cpp
#ifdef __cplusplus
extern "C" {
#endif
    
    // C 接口
    
#ifdef __cplusplus
}
#endif
```

C 接口相对来说比 C++ 稳定很多，所以使用 C 接口来封装库时，通常不用关心编译该库使用的编译器。可以看到大部分 C 库在提供时只明确了其编译时的架构和平台，而没有相关的编译器信息。

但 C 接口只是相对更稳定，并不是完全没问题，仍需注意以下问题：

**注意**：

- 类型：最好使用固定宽度类型、避免使用`bool`、枚举类型。

  > **`bool`的表示：**
  >
  > C 和 C++ 中的布尔类型并不完全等价：
  >
  > ```cpp
  > bool
  > _Bool
  > BOOL
  > ```
  >
  > Windows 中：
  >
  > ```cpp
  > typedef int BOOL;
  > ```
  >
  > 所以：
  >
  > ```
  > BOOL：通常 4 字节
  > C++ bool：通常 1 字节
  > ```
  >
  > 接口中如果双方语言、编译器或 FFI 环境不同，尽量不要直接暴露 `bool`。
  >
  > 推荐：
  >
  > ```cpp
  > typedef uint8_t VC_Bool;
  > 
  > #define VC_FALSE ((VC_Bool)0)
  > #define VC_TRUE  ((VC_Bool)1)
  > ```
  >
  > 
  >
  > **枚举大小**：
  >
  > C 和 C++ 中枚举的底层类型可能由编译器决定。
  >
  > 危险接口：
  >
  > ```
  > typedef enum VC_Status
  > {
  >     VC_OK,
  >     VC_ERROR
  > } VC_Status;
  > ```
  >
  > 不同编译器选项可能影响枚举大小，例如某些编译器支持“使用最小可容纳类型”的选项。
  >
  > 更稳妥的方式是将 ABI 类型定义成固定宽度整数：
  >
  > ```
  > typedef int32_t VC_Status;
  > 
  > #define VC_STATUS_OK              ((VC_Status)0)
  > #define VC_STATUS_INVALID_ARG     ((VC_Status)1)
  > #define VC_STATUS_INTERNAL_ERROR  ((VC_Status)2)
  > ```
  >
  > 也可以保留枚举用于源码可读性，但明确 ABI 字段使用 `int32_t`。

- 结构体布局、对齐和填充

  > 即使是纯 C 结构体，也存在布局问题。
  >
  > 例如：
  >
  > ```
  > typedef struct VC_Config
  > {
  >     uint8_t enabled;
  >     uint32_t width;
  > } VC_Config;
  > ```
  >
  > 常见布局可能是：
  >
  > ```
  > enabled：偏移 0
  > 填充：3 字节
  > width：偏移 4
  > sizeof：8
  > ```
  >
  > 如果另一模块使用：
  >
  > ```
  > #pragma pack(push, 1)
  > ```
  >
  > 可能变成：
  >
  > ```
  > enabled：偏移 0
  > width：偏移 1
  > sizeof：5
  > ```
  >
  > 因此必须注意：
  >
  > - `#pragma pack`；
  > - 编译器对齐选项；
  > - 平台默认对齐；
  > - 成员顺序；
  > - 成员类型；
  > - 指针大小；
  > - 条件编译宏。
  >
  > 建议：
  >
  > ```
  > typedef struct VC_Config
  > {
  >     uint32_t struct_size;
  >     uint32_t version;
  > 
  >     uint32_t width;
  >     uint32_t height;
  >     uint32_t flags;
  > } VC_Config;
  > ```
  >
  > 并在 C++ 实现中检查：
  >
  > ```
  > static_assert(sizeof(VC_Config) == 20);
  > static_assert(offsetof(VC_Config, width) == 8);
  > ```
  >
  > 不过如果你希望长期演进结构体，不应只依赖固定 `sizeof`，更推荐下面的版本化方案。

- 结构体版本演进

  > 旧版本：
  >
  > ```
  > typedef struct VC_Config
  > {
  >     uint32_t width;
  >     uint32_t height;
  > } VC_Config;
  > ```
  >
  > 新版本直接增加：
  >
  > ```
  > uint32_t flags;
  > ```
  >
  > 旧调用方仍然只分配旧大小，新库如果直接读取 `flags`，就会越界。
  >
  > 推荐结构：
  >
  > ```
  > typedef struct VC_Config
  > {
  >     uint32_t struct_size;
  >     uint32_t version;
  > 
  >     uint32_t width;
  >     uint32_t height;
  > 
  >     uint32_t flags;
  > } VC_Config;
  > ```
  >
  > 调用方初始化：
  >
  > ```
  > VC_Config config = {0};
  > config.struct_size = sizeof(config);
  > config.version = VC_CONFIG_VERSION_1;
  > ```
  >
  > 库中按大小判断：
  >
  > ```
  > if (config->struct_size >=
  >     offsetof(VC_Config, flags) + sizeof(config->flags))
  > {
  >     flags = config->flags;
  > }
  > ```
  >
  > 这样将来可以在尾部增加字段。
  >
  > 原则是：
  >
  > > 可以在结构体尾部追加字段，但不要插入、删除、重排已有字段。

- 不透明类型必须真正不透明

  > 推荐：
  >
  > ```
  > typedef struct VC_Core VC_Core;
  > 
  > VC_Status vc_core_create(VC_Core** out_core);
  > void vc_core_destroy(VC_Core* core);
  > ```
  >
  > 头文件中只前置声明：
  >
  > ```
  > typedef struct VC_Core VC_Core;
  > ```
  >
  > 不要定义：
  >
  > ```
  > typedef struct VC_Core
  > {
  >     void* impl;
  >     uint32_t state;
  > } VC_Core;
  > ```
  >
  > 否则调用方会知道：
  >
  > - 结构体大小；
  > - 字段布局；
  > - 内部实现；
  > - 可能自行复制或修改字段。
  >
  > 真正的不透明指针可以让库内部自由修改实现。
  >
  > 另一种方式是整数句柄：
  >
  > ```
  > typedef uint64_t VC_Handle;
  > ```
  >
  > 但要规定：
  >
  > - `0` 是否表示无效；
  > - 句柄能否复制；
  > - 是否线程安全；
  > - 销毁后再次调用如何处理；
  > - 是否包含 generation 防止陈旧句柄；
  > - 句柄是否只对当前进程有效。

- 内存管理

  > **内存分配与释放**：
  >
  > 这是 C ABI 中最重要的问题之一。
  >
  > 危险接口：
  >
  > ```
  > char* vc_get_name();
  > ```
  >
  > 调用方不知道：
  >
  > - 用 `free` 释放；
  > - 用 `delete[]` 释放；
  > - 用库专用函数释放；
  > - 还是根本不能释放。
  >
  > 不要让一个模块分配，另一个模块随意释放。
  >
  > 
  >
  > **对象创建和销毁必须成对**：
  >
  > 危险设计：
  >
  > ```
  > VC_Core* vc_create_core();
  > ```
  >
  > 调用方：
  >
  > ```
  > delete core;
  > ```
  >
  > 这是错误的，因为调用方不应该知道对象如何创建。
  >
  > 应该提供：
  >
  > ```
  > VC_Status vc_core_create(VC_Core** out_core);
  > void vc_core_destroy(VC_Core* core);
  > ```
  >
  > 原则：
  >
  > > 哪个模块创建对象，就由哪个模块负责销毁对象。
  >
  > 同样适用于：
  >
  > - 字符串；
  > - 数组；
  > - 错误对象；
  > - 图像缓冲区；
  > - 回调上下文；
  > - 文件句柄包装对象。

- C++ 异常不能跨 C 接口

  > 虽然接口声明为：
  >
  > ```
  > extern "C" VC_Status vc_process();
  > ```
  >
  > 实现内部仍然可能抛异常：
  >
  > ```
  > extern "C" VC_Status vc_process()
  > {
  >     throw std::runtime_error("failed");
  > }
  > ```
  >
  > 这会让异常越过 C ABI 边界，属于严重设计错误。
  >
  > 所有导出函数都应捕获异常：
  >
  > ```
  > extern "C" VC_Status vc_process()
  > {
  >     try
  >     {
  >         process_impl();
  >         return VC_STATUS_OK;
  >     }
  >     catch (const std::bad_alloc&)
  >     {
  >         return VC_STATUS_OUT_OF_MEMORY;
  >     }
  >     catch (const std::exception& exception)
  >     {
  >         vc_set_last_error(exception.what());
  >         return VC_STATUS_INTERNAL_ERROR;
  >     }
  >     catch (...)
  >     {
  >         vc_set_last_error("unknown error");
  >         return VC_STATUS_INTERNAL_ERROR;
  >     }
  > }
  > ```
  >
  > 导出函数最好满足：
  >
  > ```
  > noexcept
  > ```
  >
  > 例如：
  >
  > ```
  > extern "C" VC_Status vc_process() noexcept;
  > ```
  >
  > 但仍然应在内部捕获异常，因为异常逃出 `noexcept` 函数会调用 `std::terminate()`

除以上注意事项外，实际还有一些更深入的注意点，此处不再展开。



### 统一编译环境

在这种情况下，库提供时通常会附带编译器信息，例如 Qt，安装时除了选择系统平台和架构外，还需要选择你需要的编译器版本，因为 Qt 提供的是纯 C++ 库，为了保证不出 ABI 兼容问题，用户需要使用和库版本相同的编译器版本。

在这种情况下，需要注意的问题反而没有使用 C 接口时多，因为基本可以保证不会出现 ABI 问题。缺点是如果是基于第三方 C++ 库开发的自己的 C++ 库，通常也需要提供一整组版本的编译结果。

