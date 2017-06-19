/*
Copyright(c) 2017 Reza Ali syed.reza.ali@gmail.com www.syedrezaali.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

#include "cinder/CameraUi.h"
#include "cinder/Signals.h"
#include "cinder/app/App.h"
#include "cinder/app/Window.h"

namespace reza {
namespace cam {
typedef std::shared_ptr<class EasyCamera> EasyCameraRef;
class EasyCamera {
  public:
	static EasyCameraRef create( const ci::app::WindowRef &window = ci::app::getWindow() )
	{
		return EasyCameraRef( new EasyCamera( window ) );
	}
	virtual ~EasyCamera();

	void setup();
	void update();
	void enable();
	void disable();

	ci::CameraPersp &getCameraPersp()
	{
		return mCam;
	}

	float &getFov()
	{
		return mFov;
	}

  protected:
	EasyCamera( const ci::app::WindowRef &window );

	ci::app::WindowRef mWindowRef = nullptr;
	ci::CameraPersp mCam;
	ci::CameraUi mMayaCam;
	float mFov = 60.0f;
	float mCamDistance = 4.0f;
	float mNearClip = 0.10f;
	float mFarClip = 1000.0f;
	float mDoubleClickThreshold = 0.2f;
	float mLastClick = -1.0f;
	ci::signals::ScopedConnection mCameraMouseDownCb, mCameraMouseDragCb;
};
} // namespace cam
} // namespace reza
