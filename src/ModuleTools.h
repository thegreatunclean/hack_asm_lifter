//
// Created by rob on 7/16/2020.
//

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"


#ifndef HACK_LIFTER_MODULEOPTIMIZER_H
#define HACK_LIFTER_MODULEOPTIMIZER_H

using namespace llvm;

namespace hacklift {
    void optimize_module(llvm::Module*);
    void print_module(llvm::Module*);
    void verify_module(llvm::Module*);

    int run(std::unique_ptr<Module>&, std::unique_ptr<LLVMContext>&, const std::string& func_name);
}

#endif //HACK_LIFTER_MODULEOPTIMIZER_H
