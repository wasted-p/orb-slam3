// g2o - General Graph Optimization
// Copyright (C) 2011 H. Strasdat
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

#include <Eigen/Eigen>
Eigen::Matrix3d skew(const Eigen::Vector3d &v) {
  Eigen::Matrix3d m;
  m.fill(0.);
  m(0, 1) = -v(2);
  m(0, 2) = v(1);
  m(1, 2) = -v(0);
  m(1, 0) = v(2);
  m(2, 0) = -v(1);
  m(2, 1) = v(0);
  return m;
}

Eigen::Vector3d deltaR(const Eigen::Matrix3d &R) {
  Eigen::Vector3d v;
  v(0) = R(2, 1) - R(1, 2);
  v(1) = R(0, 2) - R(2, 0);
  v(2) = R(1, 0) - R(0, 1);
  return v;
}

Eigen::Vector2d project(const Eigen::Vector3d &v) {
  Eigen::Vector2d res;
  res(0) = v(0) / v(2);
  res(1) = v(1) / v(2);
  return res;
}

Eigen::Vector3d project(const Eigen::Vector4d &v) {
  Eigen::Vector3d res;
  res(0) = v(0) / v(3);
  res(1) = v(1) / v(3);
  res(2) = v(2) / v(3);
  return res;
}

Eigen::Vector3d unproject(const Eigen::Vector2d &v) {
  Eigen::Vector3d res;
  res(0) = v(0);
  res(1) = v(1);
  res(2) = 1;
  return res;
}

Eigen::Vector4d unproject(const Eigen::Vector3d &v) {
  Eigen::Vector4d res;
  res(0) = v(0);
  res(1) = v(1);
  res(2) = v(2);
  res(3) = 1;
  return res;
}
