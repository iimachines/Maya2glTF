#pragma once

inline MTime getFrameTime(const int frameIndex, const double framesPerSecond)
{
	return MTime(frameIndex / framesPerSecond, MTime::kSeconds);
}

inline void setCurrentTime(const MTime time, const bool shouldRedraw)
{
	MAnimControl::setCurrentTime(time);

	if (shouldRedraw)
	{
		M3dView::active3dView().refresh(true, true);
	}
}
