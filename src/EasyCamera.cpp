#include "EasyCamera.h"

using namespace ci;
using namespace ci::app;

namespace reza {
namespace cam {

EasyCamera::EasyCamera( const ci::app::WindowRef &window )
	: mWindowRef( window )
{
}

EasyCamera::~EasyCamera()
{
}

void EasyCamera::setup()
{
	mFov = 60.0f;
	mNearClip = 0.10f;
	mFarClip = 10000.0f;
	mCam.setWorldUp( vec3( 0.0f, 1.0f, 0.0f ) );
	update();
	mCam.lookAt( vec3( 0.0f, 0.0f, mCamDistance ), vec3( 0.0f, 0.0f, 0.0f ) );
	mMayaCam.setCamera( &mCam );
}

void EasyCamera::update()
{
	if( mWindowRef ) {
		mCam.setPerspective( mFov, mWindowRef->getAspectRatio(), mNearClip, mFarClip );
	}
}

void EasyCamera::enable()
{
	mCameraMouseDownCb = mWindowRef->getSignalMouseDown().connect( [this]( MouseEvent event ) {
		if( ( ( getElapsedSeconds() - mLastClick ) < mDoubleClickThreshold ) && !event.isMetaDown() ) {
			setup();
		}
		mLastClick = static_cast<float>( getElapsedSeconds() );
		mMayaCam.mouseDown( event.getPos() );
	} );
	mCameraMouseDragCb = mWindowRef->getSignalMouseDrag().connect( [this]( MouseEvent event ) {
		mMayaCam.mouseDrag( event.getPos(), event.isLeftDown(), event.isMiddleDown(), event.isRightDown() );
	} );
}

void EasyCamera::disable()
{
	mCameraMouseDownCb.disconnect();
	mCameraMouseDragCb.disconnect();
}
} // namespace cam
} // namespace reza