#ifndef WINDOW_ITEM_H
#define WINDOW_ITEM_H

#include <string>
#include <vector>

class window_item;
typedef std::vector< window_item* > window_list;


class window_item
{
public:
	window_item( std::wstring title, std::wstring process, HWND handle );

	std::wstring get_title() const { return _title; };
	std::wstring get_process_name() const { return _process_name; };
	std::wstring get_lower_title() const { return _lower_title; }

	HWND get_handle() const { return _handle; }

	static window_list *get_window_list();
	
private:
	std::wstring _title;
	std::wstring _lower_title;
	std::wstring _process_name;
	HWND _handle;
};



#endif