//
// Created by rob on 7/17/20.
//

#include <iostream>
#include <string>
#include <array>
#include <llvm/Support/raw_ostream.h>
#include "hacklift/create_void_function.h"
#include "hacklift/ModuleTools.h"
#include "llvm/ExecutionEngine/Orc/ThreadSafeModule.h"

using namespace llvm;

int main() {
    auto ctx = std::make_unique<LLVMContext>();
    auto mod = std::make_unique<Module>("module", *ctx);
    //auto tsm = orc::ThreadSafeModule( std::move(mod), std::move(ctx));

    //tsm.withModuleDo([](Module& M){ hacklift::create_void_function(M, "f");});
    hacklift::create_void_function(*mod, "f");

    hacklift::verify_module(*mod);
    std::cout << "Unoptimized: (" << mod->getFunction("f")->getInstructionCount() << " insts)" << std::endl;
    hacklift::print_module(*mod);

    hacklift::optimize_module(*mod);

    std::cout << "\nOptimized: (" << mod->getFunction("f")->getInstructionCount() << " insts)" << std::endl;
    hacklift::print_module(*mod);

    //Setup memory for transpiled code to act on
    std::array<int16_t, 32768> mem{0};
    mem[0] = 0x32;
    mem[1] = 0x55;
    //::run will print a before/after and return value

    hacklift::run_void_func(std::move(mod), std::move(ctx), "f", mem);

    /*
    auto ctx = std::make_unique<LLVMContext>();
    auto mod = std::make_unique<Module>("module", *ctx);

    hacklift::create_void_function(mod.get(), "f");

    hacklift::verify_module(mod.get());
    std::cout << "Unoptimized:\n" << hacklift::to_string(mod.get()) << std::endl;
    hacklift::optimize_module(mod.get());
    std::cout << "\nOptimized:\n" << hacklift::to_string(mod.get()) << std::endl;

    std::array<int16_t, 16> mem{0};
    mem[0] = 5;
    mem[1] = 8;
    hacklift::run(mod, "f", mem);
     */
    return 0;
}
