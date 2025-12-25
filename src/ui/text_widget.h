#ifndef TEXT_WIDGET_H_
#define TEXT_WIDGET_H_

#include "widget.h"

#include <string>

class TextWidget : public Widget
{
private:
	std::string m_text;
	bool m_isHighlighted;
public:
	TextWidget(std::string text, bool isHighlighted);
};

#endif // TEXT_WIDGET_H_
