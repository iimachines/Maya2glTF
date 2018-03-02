#pragma once

class ExportableClip;

class ExportableItem
{
public:
	ExportableItem();
	virtual ~ExportableItem() = 0;

	virtual std::unique_ptr<ExportableClip> createClip(const std::string& clipName, const int frameCount);

private:
	DISALLOW_COPY_AND_ASSIGN(ExportableItem);
};
