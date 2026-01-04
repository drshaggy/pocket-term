#ifndef LIST_WIDGET_H_
#define LIST_WIDGET_H_

#include "widget.h"

#include <vector>
#include<string>

class ListWidget : public Widget
{
private:
	std::vector<std::string> m_items;
	uint8_t m_selectedItem{0};
public:
	ListWidget(std::vector<std::string> items);
	virtual void render(Display* display, const uint16_t& x, const uint16_t& y) const override;
	virtual std::unique_ptr<Widget> clone() override;
};

#endif // LIST_WIDGET_H_
