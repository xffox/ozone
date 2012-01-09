#include "render/opengl/OpenglDrawer.h"

#include <GL/gl.h>
#ifndef _WIN32
#include <GL/glut.h>
#endif

#include <algorithm>

#include "geom/Point.h"
#include "render/Color.h"

namespace
{

struct DrawVertex
{
    void operator()(const geom::Point &point) const
    {
        glVertex3f(point.x, point.y, point.z);
    }
};

}

namespace render
{
namespace opengl
{
OpenglDrawer::OpenglDrawer()
{
}

void OpenglDrawer::move(float x, float y, float z)
{
    glMatrixMode(GL_MODELVIEW);
    glTranslatef(-x, -y, -z);
}

void OpenglDrawer::rotate(float angleDegrees, float x, float y, float z)
{
    glMatrixMode(GL_MODELVIEW);
    glRotatef(-angleDegrees, x, y, z);
}

void OpenglDrawer::drawPoint(float x, float y, const Color &color)
{
    glMatrixMode(GL_COLOR);
    glPushMatrix();

    glColor4f(color.r, color.g, color.b, color.a);
    glBegin(GL_POINTS);
        glVertex2f(x, y);
    glEnd();

    glPopMatrix();
}

void OpenglDrawer::drawQuadrilateralsStrip(const Vertices &vertices,
        const Color &color)
{
    glMatrixMode(GL_COLOR);
    glPushMatrix();

//	glMatrixMode(GL_MODELVIEW);
//    glPushMatrix();

//	glLoadIdentity();

    glColor4f(color.r, color.g, color.b, color.a);
    glBegin(GL_QUAD_STRIP);
        std::for_each(vertices.begin(), vertices.end(), DrawVertex());
    glEnd();

//    glPopMatrix();

    glMatrixMode(GL_COLOR);
    glPopMatrix();
}

void OpenglDrawer::drawText(const std::string &text, float x, float y)
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();

    glLoadIdentity();
    glOrtho(.0f, 1000.0f, .0f, 1000.0f, .0f, 1.0f);

    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();

    glLoadIdentity();
    glTranslatef(x, y, 0.0f);
    glScalef(0.5f, 0.5f, 0.5f);

    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(1.0);
    drawString(text);
            
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}

void OpenglDrawer::drawString(const std::string &str)
{
    // TODO: need crossplatform implementation
#ifndef _WIN32
    const size_t length = str.size();
    for(size_t i = 0; i < length;
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, str[i++]));
#endif
}

}
}
