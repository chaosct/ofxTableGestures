#ifndef _TEST_APP
#define _TEST_APP

#include "TableApp.hpp"

class testApp : public TableApp{

	public:
		void Setup();
		void Update();
		void Draw();
		void WindowResized(int w, int h);

};

#endif
