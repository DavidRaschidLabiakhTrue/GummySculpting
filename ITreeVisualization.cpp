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
	forall(vert, itreeDrawContainer.itreeDrawVertex)
	{
		vert.loadColorAs255(255, 0, 0);
		say "V:" spc vert.position.x spc vert.position.y spc vert.position.z done;
	}
	itreeDrawContainer.bindContainer();

	say "ITree Vertice Count" spc itreeDrawContainer.itreeDrawVertex.size() done;
	say "Itree Indice Count" spc itreeDrawContainer.itreeDrawIndices.size() done;


	
}
