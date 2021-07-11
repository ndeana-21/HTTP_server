#ifndef RESPONCE_HPP
# define RESPONCE_HPP

class Responce
{
	private:

	public:
		Responce();
		Responce(const Responce &copy);
		Responce &operator=(Responce const &other);
		~Responce();
};

#endif