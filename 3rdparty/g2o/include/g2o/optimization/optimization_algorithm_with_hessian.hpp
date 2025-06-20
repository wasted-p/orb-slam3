// g2o - General Graph Optimization
// Copyright (C) 2011 R. Kuemmerle, G. Grisetti, W. Burgard
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
// IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
// TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
// PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
// TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef G2O_OPTIMIZATION_ALGORITHM_WITH_HESSIAN_H
#define G2O_OPTIMIZATION_ALGORITHM_WITH_HESSIAN_H

#include "g2o/optimization/optimization_algorithm.hpp"

namespace g2o {

class Solver;

/**
 * \brief Base for solvers operating on the approximated Hessian, e.g.,
 * Gauss-Newton, Levenberg
 */
class OptimizationAlgorithmWithHessian : public OptimizationAlgorithm {
public:
  explicit OptimizationAlgorithmWithHessian(Solver *solver);
  virtual ~OptimizationAlgorithmWithHessian();

  virtual bool init(bool online = false);

  virtual bool
  computeMarginals(SparseBlockMatrix<MatrixXd> &spinv,
                   const std::vector<std::pair<int, int>> &blockIndices);

  virtual bool buildLinearStructure();

  virtual void updateLinearSystem();

  virtual bool updateStructure(const std::vector<HyperGraph::Vertex *> &vset,
                               const HyperGraph::EdgeSet &edges);

  //! return the underlying solver used to solve the linear system
  Solver *solver() { return _solver; }

  /**
   * write debug output of the Hessian if system is not positive definite
   */
  virtual void setWriteDebug(bool writeDebug);
  virtual bool writeDebug() const { return _writeDebug->value(); }

protected:
  Solver *_solver;
  Property<bool> *_writeDebug;
};

} // namespace g2o

#endif
