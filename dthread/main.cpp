#include <iostream>
#include "../gtest/gtest.h"

#include "dthread.h"

void* f(void*) {
    std::cerr << "thread 1 launched" << std::endl;
    return nullptr;
}

TEST(basics, thread_create) {
    dthread t;
}

TEST(basics, thread_create_voidptr) {
    dthread t(f, nullptr);
    t.join();
}

TEST(basics, thread_create_function) {
    dthread t([] { std::cerr << "thread 2 launched" << std::endl; });
    t.join();
}

TEST(convenience, thread_attr_empty) {
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    dthread t(&attr, [] (int x) { std::cerr << "thread 3 launched!: x = " << x << std::endl; }, 10);
    pthread_attr_destroy(&attr);
    t.join();
}

TEST(convenience, thread_attr_stack_size) {
    pthread_attr_t attr;

    void* stack;
    int ps = getpagesize();

    posix_memalign(&stack, ps, ps * 10);
    pthread_attr_init(&attr);

    size_t stack_size;
    void* stackaddr = nullptr;

    pthread_attr_getstack(&attr, &stackaddr, &stack_size);
    std::cerr << "stack size = " << stack_size << std::endl;

    if (pthread_attr_setstack(&attr, stack, ps * 10))
        throw std::runtime_error("failed to change stack_size");

    dthread t([] { std::cerr << "thread 4 launched" << std::endl; });
    pthread_attr_destroy(&attr);
    t.join();

    free(stack);
}