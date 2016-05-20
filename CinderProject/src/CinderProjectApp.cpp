#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Camera.h"
#include "cinder/params/Params.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class CinderProjectApp : public AppNative {
    CameraPersp camera;
    Quatf sceneRotation;
    Vec3f eyePosition;
    Vec3f objectPosition;
	Vec3f x_vector;
	Vec3f y_vector;
	float cameraDistance;

 params::InterfaceGl cameraParams;
  public:
    void setup() {
		x_vector.x=1;
		y_vector.y=1;
        objectPosition =  Vec3f::zero();
        cameraDistance = 500; 
        camera.setPerspective( 60.0f, getWindowAspectRatio(), 5.0f, 3000.0f );

        cameraParams = params::InterfaceGl( "Camera Settings", Vec2i( 225, 200 ) ); 
        cameraParams.addParam( "Scene Rotation", &sceneRotation );
        cameraParams.addParam( "Eye Distance", &cameraDistance, "min=50.0 max=1000.0 step=50.0 keyIncr=s keyDecr=w" );
    }

    void keyDown( KeyEvent event ) {
        if( event.getCode() == KeyEvent::KEY_UP) {
            objectPosition.y += 10;
        }
        if( event.getCode() == KeyEvent::KEY_DOWN) {
            objectPosition.y -= 10;
        }
        if( event.getCode() == KeyEvent::KEY_LEFT) {
            objectPosition.x -= 10;
        }
        if( event.getCode() == KeyEvent::KEY_RIGHT) {
            objectPosition.x += 10;
        }
    }

    void update() {
        eyePosition = Vec3f( 0.0f, 0.0f, cameraDistance );
        camera.lookAt( eyePosition, Vec3f::zero(), Vec3f::yAxis() );
        gl::setMatrices( camera );

        gl::rotate( sceneRotation );
    }

    void draw() {
        gl::clear( Color( 0.0f, 0.0f, 0.0f));
		glColor3f(1.0f,1.0f,1.0f);
        gl::drawSphere(objectPosition , 15);  
		gl::drawCube(objectPosition, Vec3f( 10.0f, 45.0f, 1.0f ) );
		gl::drawCube(objectPosition - 60*(y_vector), Vec3f( 45.0f, 75.0f, 1.0f ) );
		gl::drawCube(objectPosition - 40*(y_vector), Vec3f( 215.0f, 15.0f, 1.0f ) );
		gl::drawCube(objectPosition - 55*(y_vector), Vec3f( 195.0f, 15.0f, 1.0f ) );
		gl::drawCube(objectPosition - 70*(y_vector), Vec3f( 175.0f, 15.0f, 1.0f ) );
		gl::drawCube(objectPosition - 95*(y_vector) + 25*(x_vector), Vec3f( 20.0f, 20.0f, 1.0f ) );
		gl::drawCube(objectPosition - 95*(y_vector)- 25*(x_vector), Vec3f( 20.0f, 20.0f, 1.0f ) );
        cameraParams.draw();
    }
};

CINDER_APP_NATIVE( CinderProjectApp, RendererGl )