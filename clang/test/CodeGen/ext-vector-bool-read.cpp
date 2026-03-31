// RUN: %clang_cc1 -triple x86_64-unknown-linux-gnu -emit-llvm -o - %s | FileCheck %s
// RUN: %clang_cc1 -triple x86_64-unknown-linux-gnu -emit-llvm -O2 -o - %s | FileCheck %s

// Regression test for GH#189260: Clang crashed with an assertion failure
// in InsertElementInst when storing to an element of an ext_vector_type
// with bool element type.

typedef __attribute__((ext_vector_type(32))) bool v32bool;
v32bool v32b = {};

// CHECK-LABEL: @_Z5test1v
void test1() {
    // CHECK: insertelement <32 x i1>
    v32b[0] = true;
}

// CHECK-LABEL: @_Z5test2v
void test2() {
    // CHECK: insertelement <32 x i1>
    v32b[31] = true;
}
