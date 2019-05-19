#include "stdafx.h"
#include "CMainDlgPresenter.h"
#include "CEquationSolver.h"
#include "IChartView.h"
#include "IHarmonicCollection.h"
#include "IMainDlgView.h"

CMainDlgPresenter::CMainDlgPresenter(IHarmonicCollection& solver, IMainDlgView& view)
	: m_solver(solver)
	, m_view(view)
{
	m_view.DoOnAmplitudeChange(std::bind(&CEquationSolver::SetQuadraticCoeff, &m_solver, std::placeholders::_1));
	m_view.DoOnFrequencyChange(std::bind(&CEquationSolver::SetLinearCoeff, &m_solver, std::placeholders::_1));
	m_view.DoOnPhaseChange(std::bind(&CEquationSolver::SetConstantCoeff, &m_solver, std::placeholders::_1));
	m_view.DoOnInit(std::bind(&CMainDlgPresenter::InitView, this));
	m_solver.DoOnSolutionChange([this] {
		UpdateSolution();
		UpdateChart();
	});
}

void CMainDlgPresenter::InitView()
{
	//m_view.SetHarmonicParams(m_solver.GetQuadraticCoeff(), m_solver.GetLinearCoeff(), m_solver.GetConstantCoeff());
	//UpdateSolution();
	//UpdateTable(); TODO::update table
	UpdateChart();
}

void CMainDlgPresenter::UpdateSolution()
{
	struct SolutionPrinter : boost::static_visitor<void>
	{
		IMainDlgView& view;
		SolutionPrinter(IMainDlgView& view)
			: view(view)
		{
		}
		void operator()(NoRealRoots)
		{
			view.SetNoSolution();
		}
		void operator()(InfiniteNumberOfRoots)
		{
			view.SetInfiniteSolutions();
		}
		void operator()(double root)
		{
			view.SetSingleSolution(root);
		}
		void operator()(const std::pair<double, double>& roots)
		{
			view.SetTwoRootsSolutuion(roots.first, roots.second);
		}
	};

	SolutionPrinter printer(m_view);
	m_solver.GetEquationRoots().apply_visitor(printer);
}

void CMainDlgPresenter::UpdateChart()
{
	IChartView::Points2D points;
	for (double x = -10.0; x <= +10; x += 0.1)
	{
		points.emplace_back(x, m_solver.CalculateValue(x));
	}
	m_view.GetChartView().SetData(points);
}
