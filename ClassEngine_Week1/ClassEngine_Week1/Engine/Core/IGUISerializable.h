#ifndef IGUISERIALIZABLE_H
#define IGUISERUALIZABLE_H

class IGUISerializable
{
public:
	IGUISerializable() {}
	virtual ~IGUISerializable() {}
	virtual void SetGuiEnabled(const bool enabled) = 0;
	virtual bool GuiEnabled() = 0;
	virtual void UpdateGUI(const float deltaTime) = 0;

private:

};

#endif // !GUISERIALIZABLE_H
