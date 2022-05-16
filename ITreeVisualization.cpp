#include "ITreeVisualization.hpp"

using namespace ITreeVisualizationDefinition;

ITreeVisualizationDefinition::ITreeVisualization::ITreeVisualization()
{
}

ITreeVisualizationDefinition::ITreeVisualization::~ITreeVisualization()
{
}

void ITreeVisualizationDefinition::ITreeVisualization::generateITreeVisualization()
{
	
	int tracker = -1;
	forall(inode, inodes)
	{
		inode.generateVisualVertices(itreeDrawContainer.itreeDrawVertex, itreeDrawContainer.itreeDrawIndices, tracker);
	}

	itreeDrawContainer.bindContainer();

	say "ITree Vertice Count" spc itreeDrawContainer.itreeDrawVertex.size() done;
	say "Itree Indice Count" spc itreeDrawContainer.itreeDrawIndices.size() done;
	
}
