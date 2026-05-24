linux 内核链表

```c
typedef struct {
        int age;
        struct list_head list;
} person;

person p;

// size_t 是 sizeof 运算符的返回类型
// size_t: unsigned integer type, 专门用来表示“大小 / 长度 / 数量”
#define offsetof(TYPE, MEMBER) ((size_t)&((TYPE *)0)->MEMBER)

// 第一行验证类型是否匹配，可以去除
#define container_of(ptr, type, member)                                        \
        ({                                                                     \
                const typeof(((type *)0)->member) *_mptr = (ptr);              \
                (type *)((char *)(_mptr) - offsetof(type, member));            \
        })
```

### 1. 理解c语言结构体的内存模型

    结构体内的元素按顺序在内存里排列，结构体内第一个元素的地址就是结构第的地址，即 `&p==&(p.age)`

### 2. list_head 是一条外挂链

    通过将 list_head 嵌入到结构体来使用，链表操作都在 list_head 上

    原结构体的地址可以通 offsetof 宏获取

    可以做到数据域与指针域分离，并达到复用效果

### 3. offsetof 宏

    假设地址 `0` 是一个 person 类型的指针，获取该指针指向 list_head 的地址，刚好就是 list_head
     相对于结构体地址的偏移量，即 `&p` 加偏移量等于 `&(p.list)`

    由于这里只进行了地址计算，并没有实际解引用，所以可以正常运行

### 4. container_of 宏

    通过 list_head 地址获取原结构体地址

    传入的是 list_head 指针，将该指针转换为 char 类型指针减去偏移量后再转换为 `type` 类型指针

> c 语言指针步长是根据类型的，char:1 long:8
>
> 由于偏移量是字节数，转换为 char 指针后进行地址运算

- https://www.cnblogs.com/yangguang-it/p/11667772.html
