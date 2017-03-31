
#ifndef PROGRAM_HH
#define PROGRAM_HH

#include <string>
#include <map>

#define GLOB_SPACE "   "

using namespace std;

class Program;

extern Program program_object;

class Program
{
	Symbol_Table global_symbol_table;
	Procedure * procedure;
	map<string, Procedure*> proc_map;

public:
	Program();
	~Program();
	void delete_all();

	void set_procedure(Procedure * proc, int line);
	void add_procedure(Procedure * proc, int line);
	bool procedure_in_proc_map(Procedure * proc);
	void set_global_table(Symbol_Table & new_global_table);

	Symbol_Table_Entry & get_symbol_table_entry(string variable);

	void print_sym();
	void print();

	bool variable_proc_name_check(string symbol);
	bool variable_in_proc_map_check(string symbol);
	bool variable_in_symbol_list_check(string variable);
	void global_list_in_proc_check();
	bool procedure_in_proc_map(string & proc_name);
	Procedure* get_procedure(string proc_name);

	// compile
	void compile();
	void print_assembly();
};

#endif
