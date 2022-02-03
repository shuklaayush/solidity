/*
	This file is part of solidity.
	solidity is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
	solidity is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	You should have received a copy of the GNU General Public License
	along with solidity.  If not, see <http://www.gnu.org/licenses/>.
*/
// SPDX-License-Identifier: GPL-3.0

#include <test/tools/ossfuzz/lpsolver/FuzzerSolverInterface.h>

using namespace solidity::fuzzer::lpsolver;
using namespace solidity::util;
using namespace std;

FuzzerSolverInterface::FuzzerSolverInterface()
{
	m_solvingState.variableNames.emplace_back("");
}

LinearExpression FuzzerSolverInterface::constant(rational _value)
{
	return LinearExpression::factorForVariable(0, _value);
}

LinearExpression FuzzerSolverInterface::variable(
	rational _factor,
	string const& _variable
)
{
	return LinearExpression::factorForVariable(variableIndex(_variable), _factor);
}

void FuzzerSolverInterface::addLEConstraint(LinearExpression _lhs, LinearExpression _rhs)
{
	_lhs -= _rhs;
	_lhs[0] = -lhs[0];
	m_solvingState.constraints.push_back({move(_lhs), false});
}

solution FuzzerSolverInterface::check()
{
	return m_solver.check(m_solvingState);
}
