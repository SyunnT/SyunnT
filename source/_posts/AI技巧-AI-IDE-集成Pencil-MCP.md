---
title: 【AI技巧】AI IDE 集成 Pencil MCP
tags:
  - AI
  - Pencil
  - MCP
categories:
  - AI
  - 使用技巧
description: 介绍在各种 AI IDE 中集成 Pencil MCP 快速生成 UI 设计稿的方法
copyright: false
abbrlink: 5d59cab1
date: 2026-03-02 10:43:05
updated: 2026-03-02 11:37:05
keywords:
---

> 改编自：https://www.53ai.com/news/LargeLanguageModel/2026012420847.html

## Pencil 插件

首先是需要在你的 AI IDE 中安装 Pencil 这个插件：

![Pencil 插件]()

经测试，vscode 和 Trae 都是支持的，而 Trae 接入的是 [Open VSX Registry](https://open-vsx.org/)，所以跟 Trae 接入了相同的插件平台的 AI IDE 应该都是可以安装的。

安装完成后，打开插件的页面：

![Pencil 页面]()

> 插件的初始化可能得等一段时间，我等了很久

等待插件初始化完成后界面就显示出来了，然后创建新的文件：

![Pencil 创建]()

就可以在画布上进行设计了，到这里，插件安装部分就结束了。



## MCP 接入

Pencil 插件安装完成后会自动为各个主流 Agent 提供 MCP 服务，可以自动接入的 Agent 如下图：

![Pencil MCP 自动接入]()

基本上主流的 Agent 都支持了，但我使用的 Trae 还没有自动支持，如果是 Pencil 插件支持的 Agent 可以直接进入下一节。

对于 Trae 来说虽然没有自动支持，但是也可以手动添加 MCP 服务，具体流程如下图所示：

![Pencil MCP 文件内容提取]()

![Trae MCP 添加]()

只要看到下图所示的效果就证明添加成功了：

![Trae MCP 验证]()

其他的 Agent 配置方法应该类似。



## Vibe Design

上述配置完成后就可以进行 Vibe Design 了。

发送给 AI 的请求最好明确说明调用什么 MCP 服务，而且需要将 Agent 设置为支持 MCP 的模式，以 Trae 为例的话，需要使用 “Builder with MCP” 这个智能体：

![Choose Builder with MCP]()

对于其他的 Agent 来说可能没有把智能体像 Trae 这样拆解，所以具体情况也得具体分析，总之只要你使用的 Agent 正确接入了 Pencil MCP 服务并能够调用 MCP 接口就行。

具体流程就不多介绍了，下面展示一下实际效果：

![效果图]()



## 结语

和 Vibe Coding 一样，在没有明确的设计文档的情况下，只靠对话去生成设计稿肯定和你的想象会有些出入，你可以继续和 AI 对话来进行细节上的调整，也可以手动介入去做后续的修缮。

我个人的想法是，用这个方法去生成 UI 设计文件的初稿，无论后续是否人工介入，都能极大提高生产力。
