#ifndef SculptBrush_HPP
#define SculptBrush_HPP

#include "Sampler.hpp"
#include "SculptPayload.hpp"

#include "Cursor3D.hpp"

#include "MainDirective.hpp" // Execute Mesh Switching.

namespace SculptBrushDefinition
{
    using namespace SamplerDefinition;
    using namespace SculptPayloadDefinition;
    using namespace _Cursor3D;

    enum BrushState
    {
        BrushStateSmooth,
        BrushStateStroke,
        BrushStateColor,
        BrushStateNoise,
        BrushStateSmoothedColor,
        BrushDirac,
		BrushBrush,
        BrushTessellate,
        BrushDecimate,
        BrushInflate,
        BrushSpin,
        BrushFold,
        BrushProcessSelect,
        BrushNone
    };

    class SculptBrush : public Sampler
    {
        public:
            SculptBrush();
            ~SculptBrush();
            SculptBrush(bool trueConstructor);

            void applySculpt(MeshReference cMesh);

            void querySculpt(MeshReference cMesh);

            BrushState currentState = BrushStateColor;
            bool shouldApplySymmetrically = false;
            SculptPayload payload;
            Cursor3D cursor;

            void drawCursor();

        protected:
            double rateTime;
            double offsetTime;
            double sculptRate;
    };
} // namespace SculptBrushDefinition

#endif // !SculptBrush_HPP
