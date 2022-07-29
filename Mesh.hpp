#ifndef Mesh_HPP
#define Mesh_HPP

#include "GraphicsData.hpp"
#include "TopologyComputation.hpp"
#include "MeshStats.hpp"



#include "Octree.hpp"
#include "Decimation.hpp"

#include "MeshChangeLog.hpp"

#include "MeshHistory.hpp"

#include <variant>
#include <unordered_map>
#include <functional>

#include "UndoRedo.hpp"


namespace MeshDefinition
{
	using namespace GraphicsDataDefinition;
	using namespace MeshStatsDefinition;
	using namespace TopologyComputationDefinition;


	using namespace OctreeDefinition;
	using namespace _Decimation;
	using namespace MeshChangeLogDefinition;

	using UndoRedo_::UndoRedo;

	// a wrapper and container for all graphics and search structures used in the mesh.
	// contains graphics data for drawing
	// contains graphs and maps for searching.
	// meant as a final container for all 3d classes used for managing vertices and triangles ultimately.

	extern int MeshIDTracker;

	class Mesh : public Decimation, public UndoRedo
	{
		public:
			Mesh();
			~Mesh();

			void generateGraphsAndTrees();

			KeyData searchLinear(rv3 direction, rv3 origin);
			KeyData searchLinearParallel(rv3 direction, rv3 origin);

			static const inline v4 defaultMeshColor = v4(0.7, 0.7, 0.7, 1.0);

			void revertHistory();

			void forwardHistory();

			void undoHistory();
			void redoHistory();

			void storeUndoAndCurrent();
			void storeChanged();
			void saveSavedVerticesToUndo();

			void saveCurrentSetToStack();

			void cullHistory(ChangeLogLevel levelsUpwardToCull);
			void createVariableMap();


			void computeNormals() noexcept;
			void computeNormalsParallel();

			void computeAverageArea();

			void computeNormalsFromMatrix();

			void recomputeNormalsFromCurrentVertices() noexcept;
			void recomputeNormals(HistoryKeyVertexMap& apply);

			KeyList getTriangleNeighbors(KeyData tri);


			void applyModelMatrix();

			void cleanUpMesh();

			//ChangeLog history; // mesh reversion history.

			int meshID;

			bool isActive = false;

			string name;

			float avgArea = 0.0f;

			unordered_map<string, variableVariantType> meshVariables;

	};
	typedef Mesh& MeshReference;  // reference to a mesh
	typedef Mesh* MeshPTR; // pointer to a mesh
}

#endif // Mesh_HPP
