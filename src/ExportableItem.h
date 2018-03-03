#pragma once

class NodeAnimation;

class ExportableItem
{
public:
	ExportableItem();
	virtual ~ExportableItem() = 0;

	virtual std::unique_ptr<NodeAnimation> createAnimation(const int frameCount, const double scaleFactor);

private:
	DISALLOW_COPY_AND_ASSIGN(ExportableItem);
};
