#ifndef RENDER_VIEW_H
#define RENDER_VIEW_H

#include <memory>

namespace render
{
    class LightDrawer;

    //! Interface for rendering view.
    /*!
     * Rendering view manipulates a rendering state.
     */
    class View
    {
    public:
        virtual ~View(){}

        //! Create new light drawing object.
        /*!
         * Maximum amount of light drawing objects is implementation defined.
         */
        virtual std::auto_ptr<LightDrawer> createLightDrawer() = 0;
    };
}

#endif
