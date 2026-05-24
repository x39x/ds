#ifndef LIST_H
#define LIST_H

// NOTE: init
typedef struct list_head {
        struct list_head *next, *prev;
} list_head;

#define LIST_HAND_INIT(name) {&(name), &(name)}
#define LIST_HAND(name) struct list_head name = LIST_HAND_INIT(name)

static inline void INIT_LIST_HEAD(list_head *list) {
        list->next = list;
        list->prev = list;
}

// NOTE: add
static inline void __list_add(list_head *new, list_head *prev,
                              list_head *next) {
        next->prev = new;
        new->next = next;
        prev->next = new;
        new->prev = prev;
}

//  向 head 后添加
static inline void list_add(list_head *new, list_head *head) {
        __list_add(new, head, head->next);
}
// 向 head 前添加
static inline void list_add_tail(list_head *new, list_head *head) {
        __list_add(new, head->prev, head);
}

// NOTE: !!!important
/*
 * size_t 是 sizeof 运算符的返回类型
 *
 * size_t: unsigned integer type, 专门用来表示“大小 / 长度 / 数量”
 *
 */
#define offsetof(TYPE, MEMBER) ((size_t)&((TYPE *)0)->MEMBER)

/*
 * 第一行验证类型是否匹配
 */
#define container_of(ptr, type, member)                                        \
        ({                                                                     \
                const typeof(((type *)0)->member) *_mptr = (ptr);              \
                (type *)((char *)(_mptr) - offsetof(type, member));            \
        })

#define list_entry(ptr, type, member) container_of(ptr, type, member)

// NOTE: loop
#define list_for_each(pos, head)                                               \
        for (pos = (head)->next; pos != (head); pos = pos->next)

#define list_for_each_entry(pos, head, member)                                 \
        for (pos = list_entry((head)->next, typeof(*pos), member);             \
             &pos->member != (head);                                           \
             pos = list_entry(pos->member.next, typeof(*pos), member))

#define list_for_each_entry_reverse(pos, head, member)                         \
        for (pos = list_entry((head)->prev, typeof(*pos), member);             \
             &pos->member != (head);                                           \
             pos = list_entry(pos->member.prev, typeof(*pos), member))

// 使用临时变量 n 存储 pos，防止 pos 改变影响循环
#define list_for_each_entry_safe(pos, n, head, member)                         \
        for (pos = list_entry((head)->next, typeof(*pos), member),             \
            n = list_entry(pos->member.next, typeof(*pos), member);            \
             &pos->member != (head);                                           \
             pos = n, n = list_entry(pos->member.next, typeof(*pos), member))

#define list_for_each_entry_safe_reverse(pos, n, head, member)                 \
        for (pos = list_entry((head)->prev, typeof(*pos), member),             \
            n = list_entry(pos->member.prev, typeof(*pos), member);            \
             &pos->member != (head);                                           \
             pos = n, n = list_entry(pos->member.prev, typeof(*pos), member))

// NOTE: delete
static inline void __list_del(list_head *prev, list_head *next) {
        next->prev = prev;
        prev->next = next;
}

static inline void list_del(list_head *entry) {
        __list_del(entry->prev, entry->next);

        // 断开它的前后节点 防止误操作
        // 也可以让前后指向自己: INIT_LIST_HEAD(entry);
        entry->prev = 0;
        entry->next = 0;
}

// NOTE: misc
static inline void list_replace(list_head *old, list_head *new) {
        new->next = old->next;
        new->prev = old->prev;
        new->next->prev = new;
        new->prev->next = new;

        old->prev = 0;
        old->next = 0;
}

static inline void list_move(list_head *list, list_head *move_pos) {
        __list_del(list->prev, list->next);
        list_add(list, move_pos);
}

#define list_first_entry(ptr, type, member) list_entry(ptr, type, member)

#endif // LIST
