#pragma once
#include <iostream>
#include <string>
using namespace std;

struct Hash_functions
{
	virtual unsigned hash_function (unsigned K, unsigned N, unsigned i) = 0;
};

struct hash_function_1 : Hash_functions
{
	unsigned hash_function(unsigned K, unsigned N, unsigned i) override
	{
		if (i == 0)
		{
			return K % N;
		}
		return (hash_function(K, N, i - 1) + 1 * i + 2 * i*i) % N;
	}
} hf1;

struct hash_function_2 : Hash_functions
{
	unsigned hash_function(unsigned K, unsigned N, unsigned i) override
	{
		if (i == 0)
		{
			return K % N;
		}
		return unsigned (hash_function(K, N, i - 1) * 0.618034 * N) % N;
	}
} hf2;

struct hash_function_3 : Hash_functions
{
	unsigned hash_function(unsigned K, unsigned N, unsigned i) override
	{
		if (i == 0)
		{
			return K % N;
		}
		return (K % N + i * (1 + K % (N - 2))) % N;
	}
} hf3;

template <typename T>
class Hash_table
{
public:

	class Hash_node
	{
	public:
		Hash_node()
		{
			m_key = 0;
			m_value = T();
			m_next = -1;
			m_state = 0;
		}
		Hash_node(int key, T value, int next, int state)
		{
			m_key = key;
			m_value = value;
			m_next = next;
			m_state = state;
		}
		~Hash_node() = default;
		int m_key;
		T m_value;
		int m_state;// 0 - свободен, 1 - занят, 2 - удален
		int m_next;
	};

	Hash_table();
	Hash_table(int size);
	Hash_table(Hash_table const &ht);
	~Hash_table();
	bool add_key(int key, T value);
	void delete_key(int key);
	bool check(int key);
	int find_by_key(int key);
	void print() const;
	void change_hash_function(Hash_functions&);
	Hash_table<T> &operator= (Hash_table<T> const &ht);
	void enlarge(int amount);

private:
	int m_size;
	int m_actual_size = 0;
	Hash_node *m_table;
	Hash_functions *m_hash_function;
};

template<typename T>
Hash_table<T>::Hash_table()
{
	m_size = 1;
	m_table = new Hash_node[m_size];
	m_hash_function = &hf1;
}

template<typename T>
Hash_table<T>::Hash_table(int size)
{
	m_size = size;
	m_table = new Hash_node[m_size];
	m_hash_function = &hf1;
}

template<typename T>
Hash_table<T>::Hash_table(Hash_table const &ht)
{
	m_size = ht.m_size;
	m_table = new Hash_node[m_size];
	m_hash_function = ht.m_hash_function;
	for (int i = 0; i < ht.m_size; i++)
	{
		if (ht.m_table[i].m_state == 1)
		{
			m_table[i].m_key = ht.m_table[i].m_key;
			m_table[i].m_value = ht.m_table[i].m_value;
			m_table[i].m_next = ht.m_table[i].m_next;
			m_table[i].m_state = ht.m_table[i].m_state;
		}
	}
}

template<typename T>
 Hash_table<T>::~Hash_table()
{
	delete[] m_table;
}

 template<typename T>
 bool Hash_table<T>::add_key(int key, T value)
 {
	 if (check(key) == true)
	 {
		 return false;
	 }
	 int index = m_hash_function->hash_function(key, m_size, 1);
	 m_actual_size++;
	 if (m_actual_size > m_size)
	 {
		 cout << endl << "sorry can't do that :(";
		 m_actual_size--;
		 return false;
	 }
	 if (m_table[index].m_state != 1)
	 {
		 m_table[index].m_value = value; 
		 m_table[index].m_key = key;
		 m_table[index].m_state = 1;
		 //m_table[index].m_next = -1;
		 return true;
	 }
	 if (m_table[index].m_state == 1)
	 {
		 for (int i = 0; i < m_size; i++)
		 {
			 if (m_table[i].m_state == 0)
			 {
				 m_table[i].m_value = value;
				 m_table[i].m_key = key;
				 m_table[i].m_state = 1;
				 Hash_node *temp = &m_table[index];
				 while (temp->m_next != -1)
				 {
					 temp = &m_table[temp->m_next];
				 }
				 temp->m_next = i;
				 return true;
			 }
		 }
	 }
 }

 template<typename T>
 void Hash_table<T>::delete_key(int key)
 {
	 if (m_actual_size == 0)
	 {
		 cout << endl << "hash table is empty";
		 return;
	 }
	 int index = find_by_key(key);
	 if (index == -1)
	 {
		 cout << endl << "no such key";
		 return;
	 }
	 m_table[index].m_state = 2;
	 m_actual_size--;
 }

 template<typename T>
 bool Hash_table<T>::check(int key)
 {
	 for (int i = 0; i < m_size; i++)
	 {
		 if (m_table[i].m_key == key)
		 {
			 return true;
		 }
	 }
	 return false;
 }

 template<typename T>
 int Hash_table<T>::find_by_key(int key)
 {
	 for (int i = 0; i < m_size; i++)
	 {
		 if (m_table[i].m_key == key)
		 {
			 return i;
		 }
	 }
	 return -1;
 }

 template<typename T>
 void Hash_table<T>::change_hash_function(Hash_functions &hash_f)
 {
	 Hash_table table(m_size);
	 table.m_hash_function = &hash_f;
	 for (int i = 0; i < m_size; i++)
	 {
		 if (m_table[i].m_state == 1)
		 {
			 table.add_key(m_table[i].m_key, m_table[i].m_value);
		 }
	 }
	 *this = table;
 }

 template<typename T>
 Hash_table<T> &Hash_table<T>::operator=(Hash_table<T> const & ht)
 {
	 if (this == &ht)
	 {
		 return *this;
	 }
	 m_size = ht.m_size;
	 if (m_table)
	 {
		 delete[] m_table;
	 }
	 m_table = new Hash_node[m_size];
	 m_actual_size = ht.m_actual_size;
	 m_hash_function = ht.m_hash_function;
	 for (int i = 0; i < ht.m_size; i++)
	 {
		 if (ht.m_table[i].m_state == 1)
		 {
			m_table[i].m_key = ht.m_table[i].m_key;
			m_table[i].m_value = ht.m_table[i].m_value;
			m_table[i].m_next = ht.m_table[i].m_next;
			m_table[i].m_state = ht.m_table[i].m_state;
		 }
	 }
	 return *this;
 }

 template<typename T>
 void Hash_table<T>::enlarge(int amount)
 {
	 if (amount <= 0)
	 {
		 return;
	 }

	 Hash_table temp(*this);
	 m_size += amount;
	 delete[] m_table;
	 m_table = new Hash_node[m_size];
	 for (int i = 0; i < temp.m_size; i++)
	 {
		 if (temp.m_table[i].m_state == 1)
		 {
			 m_table[i].m_key = temp.m_table[i].m_key;
			 m_table[i].m_value = temp.m_table[i].m_value;
			 m_table[i].m_next = temp.m_table[i].m_next;
			 m_table[i].m_state = temp.m_table[i].m_state;
		 }
	 }
 }

 template<typename T>
 void Hash_table<T>::print() const
 {
	 for (int i = 0; i < m_size; i++)
	 {
		 if (m_table[i].m_state == 1)
		 {
			 cout << endl << " key = " << m_table[i].m_key << "| value = " << m_table[i].m_value << "| state = " << m_table[i].m_state;
			 cout << "| next = " << m_table[i].m_next;
		 }
	 }
 }


