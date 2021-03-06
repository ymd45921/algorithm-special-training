# 字符串模板

原有的基本 KMP 算法的模板已经完备并通过验证：[传送门>>](https://github.com/ymd45921/XCPC_pattern/blob/main/String/KMP-fix.cc)

需要注意的是，只有原始的 KMP 算法能够求出 $\text{border}$ 数组；优化改进后的 KMP 虽然可以更快的匹配，但是它生成的并<font color="red">不是 $\text{border}$ 数组</font>。虽然某些时候它们可以混用，但是还是存在本质的区别。

## 拓展 KMP

**声明**：又名 **$\text{Z Algorithm}$**，其计算产物是 $z$ 数组，称 $Z: s \to z$ 为 $Z$ 函数；

**定义**：对于长度为 n 的字符串 $s$，约定字符串下标以 0 为起点，则有 $z_i = LCP(s_{[0, n)}, s_{[i, n)})$；LCP 指两个字符串的最长公共前缀；特别地，有 $z_0 = 0$。

对比 KMP，拓展 KMP 可以在线性时间内求出模式串 $T$ 和目标串 $S$ 的所有后缀的最长公共前缀。

### 算法描述

和 KMP 算法类似，在应用之前，我们需要先在线性时间内求出串 $s$ 的 $z$ 数组。

由上面的定义可以知道 $s_{[0, z_i)} = s_{[i, i + z_i)}$；我们称区间 $[i, i + z_i)$ 为**匹配段**（Z-box），和 KMP 算法中的 border 形成对比。但 border 是针对串的一个前缀（以 $i$ 结尾）而言的，但 Z-box 只针对一个界符 $i$ 而言；两个算法匹配的公共串在界符的两侧。

在算法进行过程中，我们维护右端点最靠右侧的匹配段，记作 $[l, r]$；显然，$s_{l..r}$ 是串 $s$ 的前缀。初始状态下，$l = r = 0$；计算时，我们始终保持 $l \leq i$。

在从 $i = 1$ 开始向右遍历到长度 $n$ 计算 $z_i$ 的过程中：

- 如果 $i \leq r$，那么一定有 $s_{[i - l, r - l]} = s_{[i, r]}$；显然，此时有 $z_i \geq min(z_{i - l}, r - i + 1)$。
  - 如果 $z_{i - l}$ 更小，那么 $z_i$ 不可能有更多的拓展；因为如果有，$z_{i - l}$ 会先拓展。
  - 否则，$r$ 之后的部分仍可能称为 $z_i$ 的一部分；此时暴力拓展即可。
- 如果 $i > r$，维护的信息不能参照；所以直接从 $i$ 开始暴力比较求出 $z_i$ 即可。
- 求出 $z_i$ 之后，若 $i + z_i - 1 > r$，那么需要更新维护的区间为新的 Z-box：$[i, i + z_i - 1]$。

上述算法内层的每次暴力拓展都会使得维护的 $r$ 向右移动至少 1 位，所以暴力拓展会执行不超过 $n$ 次；而对于外层的循环，显然也是线性的遍历；综上所述，这个算法是线性时间的，$O(n)$。

### 算法应用

和 KMP 类似，$z$ 函数的应用和前缀函数也非常相似。

#### 目标串所有后缀和模式串的 LCP

这虽然没什么实际意义，但是对应了 KMP 的子串查找；设模式串是 $S$，目标串是 $T$；当然，可以像构造前缀函数那样，将两个串拼成 $S\#T$，然后在 $O(|S| + |T|)$ 的时间内运行 Z 函数求出；也可以像常规子串查找那样，处理 $S$ 的 Z 数组，然后对于每个 $T$ 使用构造 Z 数组的方法求出 LCP。

#### 匹配子串

构造字符串 $S = P + \# + T$，然后构造它的 Z 数组；扫描 $S$ 中的 $T$ 部分，如果它有 $z_t = |P|$，那么说明了存在一个 $P$ 在 $T$ 的 $t - |P| - 1$ 位置。复杂度是线性的，但是意义不明（

#### 串的最短整周期

计算其 Z 数组；最短整周期是最小的满足 $i + z_i = n$ 和 $i\ |\ n$ 的 $i$；这是显然的。

#### 本质不同子串数



## Manacher 算法

可以在线性时间内找到串的所有回文串子串；过程和 Z 算法相似。

Manacher 利用了回文串的性质：算法始终维护目前右侧边界最靠右的回文串区间，如果一个位置出现在这个区间内，那么它可以利用相当于对称中心左侧的那个节点拥有的回文串长度进行更新。

一种常用的写法是在原字符串的每两个个位置之间插入一个不存在的字符 $\#$，然后以每个字符为中点进行扩增；时间复杂度，空间复杂度都是 $O(2n)$ 的；当然也可以直接在原字符串上构造两次，空间上更优，但是使用起来更麻烦一些，这也是模板代码的实现方式。

## 最小表示算法

**定义**：若 $T = S_{[i, n)} + S_{[0, i)}$，则称串 $S$ 和串 $T$ **循环同构**；在串 $S$ 所有的循环同构中字典序最小的那个字符串称为 $S$ 的**最小表示**。

暴力是 $O(n^2)$ 的，考虑进行优化：设 $A = S_i$，$B = S_j$ 且 $S_{[i, i+k)} = S_{[j, j+k)}$；假设 $A > B$，则一定有 $S[i + k] > S[j + k]$，在这之前相等的 $k$ 个字符没有比较的意义，应当直接比较第 $k+1$ 个字符。

## AC 自动机

用来进行多模串匹配的数据结构。

首先要先将所有的模式串加入 AC 自动机维护的 Tire 树上，然后 BFS 地维护 Fail 指针构建字典树；

首先解释一下 Fail 指针的意义：和前缀数组 $\pi$ 类似，$fail[u]$ 是状态 $u$ 的一个后缀；因为使用 BFS 维护，所以深度较浅的状态的 Fail 指针已经维护过了。

设 $p = S_i$，$u = S_{i + 1}$，$s = S[i+1]$；显然，存在转移关系 $(p, s) \to u$。

- 如果 $(fail[p], s) \to v$ 存在，则令 $fail[u] = v$；这是一个显然的后缀的转移
- 如果 $(fail[p], s) \to v$ 不存在，则递归地向上寻找 $(fail[fail[p]], s) \to v'$；相当于缩短后缀范围
- 上述递归将终止于根节点，即无已匹配的后缀是有效的，重新匹配

实际实现时，因为具有递归性：若不存在，则在维护 $fail[p]$ 的时候已经维护过了，故直接赋值即可。

简单地说，fail 指针始终是的有效后缀，但不一定是最后回边选用的后缀；实际选择的后缀在构建的过程中自然的维护，因为状态的后缀对于一个位置字符处理的办法一定是传递的。

然后对于目标串进行多模匹配：每当从流中取出一个字符时，按照字典图进行状态转移；并检查当前到达的状态的前缀的每一个有效后缀是否为接收状态（即暴力跳 fail 边）直到到达空后缀。

### Fail 树优化

如果向上面那样暴力跳 Fail 边，在一个字符串上进行多模匹配的复杂度最坏是 $O(nm)$，也就是进行 $n$ 次 KMP 的复杂度；因为原本的匹配函数每当到达一个节点都会尝试跳回根节点，而这样的问题就是如果面对形如 `aaaaaa...` 的字符串，需要跳 $n$ 次 Fail。

将自动机中的 $i \to fail[i]$ 的边反向建成 Fail 树。显然，因为每当到达一个状态都会向回跳，所以实际上到达每个状态的次数包含了到达它的所有儿子的次数；因此，Fail 树优化在于匹配函数不再需要回跳，这部分的匹配由基于 Fail 树的 DFS 一次统计，时间复杂度稳定在 $O(n + m)$。