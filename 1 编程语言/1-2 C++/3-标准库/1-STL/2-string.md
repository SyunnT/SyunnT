## 一、构造与赋值

### 1. 构造

| 操作                        | 效果                                                         |
| --------------------------- | ------------------------------------------------------------ |
| 默认构造                    | 空字符串                                                     |
| 拷贝/移动                   | 允许                                                         |
| `string(cstr)`              | **隐式转换**：用 C 风格字符串`cstr`构造，被构造的`string`对象中不包含末尾空字符 |
| `string(init_list)`         | **隐式转换**：等效于`string(init_list.begin(), init_list.end())` |
| `string(count, ch)`         | 用`count`个`ch`字符初始化字符串                              |
| `string(beg, end)`          | 将字符串初始化为`[beg, end)`所指的内容。迭代器要求至少为输入迭代器 |
| `string(ptochar, count)`    | 将字符串初始化为`[ptochar, ptochar + count)`所指的内容<br />如果此范围不是有效范围，则行为未定义 |
| `string(other, pos)`        | 用另一个`string`对象`other`进行构造，从`other`的第`pos`个字符开始，到最后一个字符结束 |
| `string(other, pos, count)` | 类似于上一个构造函数。但最多只拷贝`count`个字符。如果先到达`other`的末尾则直接结束而无需`count`个字符 |

### 2. 赋值

| 操作                          | 效果                                                     |
| ----------------------------- | -------------------------------------------------------- |
| 拷贝/移动                     | 允许                                                     |
| `s = cstr`                    | 等效于`s = string(cstr)`                                 |
| `s = ch`                      | 将`string`对象`s`赋值为单个字符`ch`                      |
| `s = {char_list}`             | 等效于`s = string{char_list}`                            |
| `s.assign(const string& str)` | 等效于拷贝赋值运算符                                     |
| `s.assign(string&& str)`      | 等效于移动赋值运算符                                     |
| `s.assign(count, ch)`         | 等效于`s = string(count, ch)`                            |
| `s.assign(ptochar, count)`    | 等效于`s = string(ptochar, count)`                       |
| `s.assign(cstr)`              | 等效于`s = string(cstr)`                                 |
| `s.assign(other, pos, count)` | 等效于`s = string(other, pos, count)`                    |
| `s.assign(beg, end)`          | 等效于`s = string(beg, end)`。迭代器要求至少为输入迭代器 |
| `s.assign(init_list)`         | 等效于`s = string(init_list)`                            |



## 二、操作

### 1. 迭代器

| 操作                                     | 效果           |
| ---------------------------------------- | -------------- |
| `begin`、`cbegin`<br />`end`、`cend`     | 返回常规迭代器 |
| `rbegin`、`crbegin`<br />`rend`、`crend` | 返回反向迭代器 |

> **迭代器失效**：
>
> 



### 2. 元素访问

| 操作            | 效果                                                         |
| --------------- | ------------------------------------------------------------ |
| `at(pos)`       | 返回对指定位置`pos`处字符的引用。<br />执行边界检查，无效访问时将抛出`std::out_of_range`类型的异常。 |
| `operator[pos]` | 如果`pos < size()`，返回到指定位置`pos`字符的引用，或者如果`pos == size()`，则返回到`CharT()`的引用。 <br />不执行边界检查。 |
| `data()`        | 返回底层指向 C 风格字符串的指针                              |
| `front()`       | 返回首字符的引用                                             |
| `back()`        | 返回对字符串中最后一个字符的引用                             |



### 3. 容量

| 操作                                | 效果                                                         |
| ----------------------------------- | ------------------------------------------------------------ |
| `empty()`                           | 为空返回`true`，否则返回`false`                              |
| `size()`                            | 返回字符串中`CharT`元素的数量                                |
| `max_size()`                        | 返回由于系统或库实现限制，字符串能够容纳的最大元素数量       |
| `resize(count)`                     | 将字符串大小调整为包含`count`个字符。<br />如果当前大小小于`count`，则会追加额外的字符，追加的字符初始化为`CharT()`<br />如果当前大小大于`count`，字符串将被缩减为前`count`个元素。 |
| `resize(count, ch)`                 | 和`resize(count)`基本相同，但将追加的字符初始化为`ch`        |
| `capacity()`                        | 返回字符串当前已分配空间的字符数。                           |
| `reserve()`<br />`reserve(new_cap)` | 通知`string`对象计划的大小更改，以便它可以适当地管理存储分配：<br />- 如果`new_cap`大于当前的`capacity()`，则会分配新的存储空间，并且`capacity()`将变得等于或大于`new_cap`。<br />- 如果`new_cap`小于当前的`capacity()`，这是一个非强制性的收缩请求<br />- 如果`new_cap`小于当前的`size()`，这是一个非强制性的缩减到合适大小的请求，等效于`shrink_to_fit()` |
| `shrink_to_fit()`                   | 请求移除未使用的容量。                                       |



### 4. 修改器

| 操作                                                 | 效果                                                         |
| ---------------------------------------------------- | ------------------------------------------------------------ |
| `clear()`                                            | 从字符串中移除所有字符                                       |
| `insert(pos, args)`                                  | `pos`是一个下标，表示字符串中某个位置，`args`用于初始化被插入的内容。<br />插入位置在`pos`指示处。<br />返回插入后字符串的引用<br />`args`可以是：<br />- `count, ch`：等效于在`pos`处插入`string(count, ch)`<br />- `cstr`：等效于在`pos`处插入`string(cstr)`<br />- `ptochar, count`：等效于在`pos`处插入`string(ptochar, count)`<br />- `other`：等效于在`pos`处插入`string(other)`（拷贝构造）<br />- `other, sub_index, count`：等效于在`pos`处插入`string(other, sub_index, count)` |
| `insert(it, args)`                                   | `it`是一个迭代器，指向字符串中某个位置，`args`用于初始化被插入的内容。<br />插入位置在`it`之前。<br />返回第一个插入字符的副本的迭代器，如果未插入任何字符，则返回`it`<br />`args`可以是：<br />- `ch`：等效于在`it`前插入字符`ch`<br />- `count, ch`：等效于在`it`前插入`string(count, ch)`<br />- `beg, end`：等效于在`it`前插入`string(beg, end)`。迭代器要求至少为输入迭代器<br />- `init_list`：等效于在`it`前插入`string(init_list)` |
| `erase()`<br />`erase(pos)`<br />`erase(pos, count)` | 从索引`pos`开始移除`std::min(count, size() - pos)`个字符<br />`pos`的默认值为 0<br />`count`的默认值为 `size() - pos`<br />返回`*this` |
| `erase(it)`<br />`erase(beg, end)`                   | 移除迭代器`it`指示位置处的字符，返回指向紧随被移除字符之后的字符的迭代器<br />移除迭代器范围`[beg, end)`指示范围内的字符，返回指向在移除操作之前`end`指向的字符的迭代器； |
| `push_back(ch)`                                      | 将给定的字符`ch`追加到字符串的末尾。                         |
| `pop_back()`                                         | 移除字符串的最后一个字符。                                   |
| `swap(other)`                                        | 与另一个`string`对象`other`交换内容                          |



### 5. 查找

| 操作           | 效果 |
| -------------- | ---- |
| `s.find(args)` |      |
