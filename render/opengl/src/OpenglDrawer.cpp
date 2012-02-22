#include "render/opengl/OpenglDrawer.h"

#include <GL/gl.h>
#ifndef _WIN32
#include <GL/glut.h>
#endif

#include <algorithm>

#include "geom/Point.h"
#include "render/Color.h"
#include "render/VerticesData.h"

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
OpenglDrawer::OpenglDrawer(View &view)
    :view(view)
{
}

void OpenglDrawer::pushModelView()
{
    push(GL_MODELVIEW);
}

void OpenglDrawer::popModelView()
{
    pop(GL_MODELVIEW);
}

void OpenglDrawer::translateModelView(float x, float y, float z)
{
    translate(GL_MODELVIEW, x, y, z);
}

void OpenglDrawer::rotateModelView(float angleDegrees, float x, float y, float z)
{
    rotate(GL_MODELVIEW, angleDegrees, x, y, z);
}

void OpenglDrawer::pushProjection()
{
    push(GL_PROJECTION);
}

void OpenglDrawer::popProjection()
{
    pop(GL_PROJECTION);
}

void OpenglDrawer::translateProjection(float x, float y, float z)
{
    translate(GL_PROJECTION, x, y, z);
}

void OpenglDrawer::rotateProjection(float angleDegree,
    float x, float y, float z)
{
    rotate(GL_PROJECTION, angleDegree, x, y, z);
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
        glNormal3f(.0f, .0f, -1.0f);
        std::for_each(vertices.begin(), vertices.end(), DrawVertex());
    glEnd();

//    glPopMatrix();

    glMatrixMode(GL_COLOR);
    glPopMatrix();
}

void OpenglDrawer::drawQuadrilateralsStrip(const VerticesData &data)
{
    glBegin(GL_QUAD_STRIP);
        glNormal3f(.0f, .0f, -1.0f);
        for(std::size_t i = 0; i < data.size(); ++i)
        {
        }
    glEnd();
}

void OpenglDrawer::drawSphere(float r, const Color &color)
{
    glMatrixMode(GL_COLOR);
    glPushMatrix();

    glColor4f(color.r, color.g, color.b, color.a);
    glutSolidSphere(r, 20, 20);

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

void OpenglDrawer::push(int mode)
{
    glMatrixMode(mode);
    glPushMatrix();
}

void OpenglDrawer::pop(int mode)
{
    glMatrixMode(mode);
    glPopMatrix();
}

void OpenglDrawer::translate(int mode, float x, float y, float z)
{
    glMatrixMode(mode);
    glTranslatef(x, y, z);
}

void OpenglDrawer::rotate(int mode, float angleDegrees,
    float x, float y, float z)
{
    glMatrixMode(mode);
    glRotatef(angleDegrees, x, y, z);
}

}
}
