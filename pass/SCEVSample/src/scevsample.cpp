#include "scevsample.hpp"

bool SCEVSample::runOnLoop(llvm::Loop *L, llvm::LPPassManager &LPM){
	//getAnalysisでScalarEvolutionを取得
	llvm::ScalarEvolution *SE = &(getAnalysis<llvm::ScalarEvolution>());

	llvm::BasicBlock *latch_bb = L->getExitingBlock();
	unsigned int trip_count = SE->getSmallConstantTripCount(L, latch_bb);

	llvm::errs() << "loop trip count = " << trip_count << "\n";

	return false;
}

void SCEVSample::getAnalysisUsage(llvm::AnalysisUsage &AU) const{
	//変更を加えない
	AU.setPreservesAll();
	//ScalarEvolutionを利用するのでaddRequired
	AU.addRequired<llvm::ScalarEvolution>();
}

char SCEVSample::ID=0;
static llvm::RegisterPass<SCEVSample> X("scevsample", "analyze loop trip count using scalar evolution", false , false);
