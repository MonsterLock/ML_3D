#pragma once
#include "Global.h"

class StepTimer
{
	LARGE_INTEGER
		// Source timing data.
		mQPCFrequency,
		mQPCLastTime;

	uint64_t
		mQPCMaxDelta,
		// Timing data.
		mElapsedTicks,
		mTotalTicks,
		mLeftOverTicks,
		// Frame rate data.
		mFrameCount,
		mFPS,
		mFramesThisSecond,
		mQPCSecondCounter,
		// Configuring fixed time step mode.
		mTargetElapsedTicks;

	bool mIsFixedTimeStep;

public:
	StepTimer() noexcept( false ) :
		mElapsedTicks( 0 ),
		mTotalTicks( 0 ),
		mLeftOverTicks( 0 ),
		mFrameCount( 0 ),
		mFPS( 0 ),
		mFramesThisSecond( 0 ),
		mQPCSecondCounter( 0 ),
		mIsFixedTimeStep( false ),
		mTargetElapsedTicks( TicksPerSecond / 60 )
	{
		if( !QueryPerformanceFrequency( &mQPCFrequency ) )
			REPORTMSG( QueryPerformanceFrequency(), 0, High - resolution performance counter could not be supported. );

		if( !QueryPerformanceCounter( &mQPCLastTime ) )
			REPORTMSG( QueryPerformanceCounter(), 0, High - resolution performance counter could not retreive current value. );

		// Initialize max delta to 1/10 of a second.
		mQPCMaxDelta = static_cast< uint64_t >( mQPCFrequency.QuadPart / 10 );
	}

	// Get elapsed time since the previous Update call.
	uint64_t GetElapsedTicks() const { return mElapsedTicks; }
	double GetElapsedSeconds() const { return TicksToSeconds( mElapsedTicks ); }

	// Get total time since the start of the program.
	uint64_t GetTotalTicks() const { return mTotalTicks; }
	double GetTotalSeconds() const { return TicksToSeconds( mTotalTicks ); }

	// Get total number of updates since start of the program.
	uint32_t GetFrameCount() const { return static_cast< uint32_t >( mFrameCount ); }

	// Get the current framerate.
	uint32_t GetFramesPerSecond() const { return static_cast< uint32_t >( mFPS ); }

	// Set whether to use fixed or variable timestep mode.
	void SetFixedTimeStep( bool isFixedTimestep ) { mIsFixedTimeStep = isFixedTimestep; }

	// Set how often to call Update when in fixed timestep mode.
	void SetTargetElapsedTicks( uint64_t targetElapsed ) { mTargetElapsedTicks = targetElapsed; }
	void SetTargetElapsedSeconds( double targetElapsed ) { mTargetElapsedTicks = SecondsToTicks( targetElapsed ); }

	// Integer format represents time using 10,000,000 ticks per second.
	static const uint64_t TicksPerSecond = 10000000;

	static double TicksToSeconds( uint64_t ticks ) { return static_cast< double >( ticks ) / TicksPerSecond; }
	static uint64_t SecondsToTicks( double seconds ) { return static_cast< uint64_t >( seconds * TicksPerSecond ); }

	void ResetElapsedTime()
	{
		if( !QueryPerformanceCounter( &mQPCLastTime ) )
			REPORTMSG( QueryPerformanceCounter(), 0, High - resolution performance counter could not retreive current value. );

		mLeftOverTicks = 0;
		mFPS = 0;
		mFramesThisSecond = 0;
		mQPCSecondCounter = 0;
	}

	// Update timer state, calling the specified Update function the appropriate number of times.
	//template<typename TUpdate>
	void Tick( )//const TUpdate& update )
	{
		// Query the current time.
		LARGE_INTEGER currentTime;

		if( !QueryPerformanceCounter( &currentTime ) )
			REPORTMSG( QueryPerformanceCounter(), 0, High - resolution performance counter could not retreive current value. );

		uint64_t timeDelta = currentTime.QuadPart - mQPCLastTime.QuadPart;

		mQPCLastTime = currentTime;
		mQPCSecondCounter += timeDelta;

		// Clamp excessively large time deltas (e.g. after paused in the debugger).
		if( timeDelta > mQPCMaxDelta )
			timeDelta = mQPCMaxDelta;

		// Convert QPC units into a canonical tick format. This cannot overflow due to the previous clamp.
		timeDelta *= TicksPerSecond;
		timeDelta /= mQPCFrequency.QuadPart;

		uint32_t lastFrameCount = static_cast< uint32_t >( mFrameCount );

		//if( mIsFixedTimeStep )
		//{
		//	// Fixed timestep update logic

		//	// If the app is running very close to the target elapsed time (within 1/4 of a millisecond) just clamp
		//	// the clock to exactly match the target value. This prevents tiny and irrelevant errors
		//	// from accumulating over time. Without this clamping, a game that requested a 60 fps
		//	// fixed update, running with vsync enabled on a 59.94 NTSC display, would eventually
		//	// accumulate enough tiny errors that it would drop a frame. It is better to just round
		//	// small deviations down to zero to leave things running smoothly.

		//	if( static_cast< uint64_t >( std::abs( static_cast< int64_t >( timeDelta - mTargetElapsedTicks ) ) ) < TicksPerSecond / 4000 )
		//	{
		//		timeDelta = mTargetElapsedTicks;
		//	}

		//	mLeftOverTicks += timeDelta;

		//	while( mLeftOverTicks >= mTargetElapsedTicks )
		//	{
		//		mElapsedTicks = mTargetElapsedTicks;
		//		mTotalTicks += mTargetElapsedTicks;
		//		mLeftOverTicks -= mTargetElapsedTicks;
		//		mFrameCount++;

		//		update();
		//	}
		//}
		//else
		//{
		//	// Variable timestep update logic.
		//	mElapsedTicks = timeDelta;
		//	mTotalTicks += timeDelta;
		//	mLeftOverTicks = 0;
		//	mFrameCount++;

		//	update();
		//}
		// Variable timestep update logic.
		mElapsedTicks = timeDelta;
		mTotalTicks += timeDelta;
		mLeftOverTicks = 0;
		mFrameCount++;

		// Track the current framerate.
		if( mFrameCount != lastFrameCount )
		{
			mFramesThisSecond++;
		}

		if( mQPCSecondCounter >= static_cast< uint64_t >( mQPCFrequency.QuadPart ) )
		{
			mFPS = mFramesThisSecond;
			mFramesThisSecond = 0;
			mQPCSecondCounter %= mQPCFrequency.QuadPart;
		}
	}
};