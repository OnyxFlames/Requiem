#include "Application.hpp"

void Application::pushState(std::unique_ptr<Game_State> state)
{
	states.push(std::move(state));
}
void Application::popState()
{
	states.pop();
}
void Application::changeState(std::unique_ptr<Game_State> state)
{
	states.pop();
	pushState(std::move(state));
}
std::stack<std::unique_ptr<Game_State>>& Application::get_state()
{
	return states;
}