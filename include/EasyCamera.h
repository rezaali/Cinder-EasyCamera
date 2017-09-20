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
    struct Format {
    public:
        Format() {
            mFov = 60.0f;
            mCamDistance = 4.0f;
            mNearClip = 0.10f;
            mFarClip = 1000.0f;
            mDoubleClickThreshold = 0.2f;
        }
        Format( const Format &copy )
        {
            mFov = copy.mFov;
            mCamDistance = copy.mCamDistance;
            mNearClip = copy.mNearClip;
            mFarClip = copy.mFarClip;
            mDoubleClickThreshold = copy.mDoubleClickThreshold;
        }
        Format &fov( float fov )
        {
            mFov = fov;
            return *this;
        }
        Format &distance( float distance )
        {
            mCamDistance = distance;
            return *this;
        }
        Format &near( float near )
        {
            mNearClip = near;
            return *this;
        }
        Format &far( float far )
        {
            mFarClip = far;
            return *this;
        }
        Format &clickThreshold( float clickThreshold )
        {
            mDoubleClickThreshold = clickThreshold;
            return *this;
        }
        
    protected:
        float mFov = 60.0f;
        float mCamDistance = 4.0f;
        float mNearClip = 0.10f;
        float mFarClip = 1000.0f;
        float mDoubleClickThreshold = 0.2f;
        friend class EasyCamera;
    };
    
	static EasyCameraRef create( const ci::app::WindowRef &window = ci::app::getWindow(), Format format = Format() )
	{
		return EasyCameraRef( new EasyCamera( window, format ) );
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
		return mFormat.mFov;
	}

  protected:
	EasyCamera( const ci::app::WindowRef &window, Format format = Format() );

	ci::app::WindowRef mWindowRef = nullptr;
	ci::CameraPersp mCam;
	ci::CameraUi mMayaCam;
    Format mFormat;
	float mLastClick = -1.0f;
	ci::signals::ScopedConnection mCameraMouseDownCb, mCameraMouseDragCb;
};
} // namespace cam
} // namespace reza
