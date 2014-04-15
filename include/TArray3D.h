/**
 * @file Array3D.h
 * @author Henri Keeble
 * @brief Declares and defines a template class for managing a 3D array of objects.
 * @see Array3D
 */

#ifndef ARRAY3D_H
#define ARRAY3D_H

namespace IrrGame
{
	/** A template class for managing a 3D array of objects. */
	template<class T>
	class TArray3D
	{
	public:
		TArray3D();
		TArray3D(const int& width, const int& height, const int& depth);
		TArray3D(const TArray3D& param);
		const TArray3D& operator=(const TArray3D& param);
		T* operator()(const int& x, const int& y, const int& z);
		virtual ~TArray3D();
	private:
		int width, height, depth;
		T*** array;
		
		/** Allocates memory for the data. */
		void Allocate();
		
		/** Frees all data from memory. */
		void Free();
		
		/** Copies data from one array into this array. */
		void Copy(const TArray3D& param);
	};
	
	template<class T>
	TArray3D<T>::TArray3D()
	{
		this->width = 0;
		this->height = 0;
		this->depth = 0;
		array = nullptr;
	}
	
	template<class T>
	TArray3D<T>::TArray3D(const int& width, const int& height, const int& depth)
	{
		this->width = width;
		this->height = height;
		this->depth = depth;
		
		Allocate();
	}	
	
	template<class T>
	TArray3D<T>::TArray3D(const TArray3D& param)
	{
		this->width = param.width;
		this->height = param.height;
		this->depth = param.depth;	
	
		Allocate();
		Copy(param);
	}
	
	template<class T>
	const TArray3D<T>& TArray3D<T>::operator=(const TArray3D& param)
	{
		if(this == &param)
			return *this;
		else
		{
			this->width = param.width;
			this->height = param.height;
			this->depth = param.depth;
			
			Free();
			Allocate();
			Copy(param);
		}
	}
	
	template<class T>
	T* TArray3D<T>::operator()(const int& x, const int& y, const int& z)
	{
		return &array[x][y][z];
	}
	
	template<class T>
	TArray3D<T>::~TArray3D()
	{
		Free();
	}
	
	template<class T>
	void TArray3D<T>::Allocate()
	{
		array = new T**[width];
		for(int x = 0; x < width; x++)
		{
			array[x] = new T*[height];
			for(int y = 0; y < height; y++)
				array[x][y] = new T[depth];
		}
	}
	
	template<class T>
	void TArray3D<T>::Free()
	{
		if(array)
		{
			for(int x = 0; x < width; x++)
			{
				for(int y = 0; y < height; y++)
					delete [] array[x][y];
				
				delete [] array[x];
			}
			
			delete [] array;
		}	
	}
	
	template<class T>
	void TArray3D<T>::Copy(const TArray3D& param)
	{
		for(int x = 0; x < width; x++)
		{
			array[x][0][0] = param.array[x][0][0];
			for(int y = 0; y < height; y++)
			{
				array[x][y][0] = param.array[x][y][0];
				for(int z = 0; z < depth; z++)
					array[x][y][z] = param.array[x][y][z];
			}
		}
	}
}

#endif // ARRAY3D_H
