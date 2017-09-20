#include "EasyCamera.h"

using namespace ci;
using namespace ci::app;

namespace reza {
namespace cam {

EasyCamera::EasyCamera( const ci::app::WindowRef &window, Format format )
	: mWindowRef( window ), mFormat( format )
{
}

EasyCamera::~EasyCamera()
{
}

void EasyCamera::setup()
{
	mCam.setWorldUp( vec3( 0.0f, 1.0f, 0.0f ) );
	update();
	mCam.lookAt( vec3( 0.0f, 0.0f, mFormat.mCamDistance ), vec3( 0.0f, 0.0f, 0.0f ) );
	mMayaCam.setCamera( &mCam );
}

void EasyCamera::update()
{
	if( mWindowRef ) {
		mCam.setPerspective( mFormat.mFov, mWindowRef->getAspectRatio(), mFormat.mNearClip, mFormat.mFarClip );
	}
}

void EasyCamera::enable()
{
	mCameraMouseDownCb = mWindowRef->getSignalMouseDown().connect( [this]( MouseEvent event ) {
		if( ( ( getElapsedSeconds() - mLastClick ) < mFormat.mDoubleClickThreshold ) && !event.isMetaDown() ) {
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
