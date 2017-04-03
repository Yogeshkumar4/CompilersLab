#include "common-classes.hh"
#include "error-display.hh"
#include "user-options.hh"
#include "icode.hh"
#include "reg-alloc.hh"
#include "symbol-table.hh"
#include "ast.hh"
#include "procedure.hh"
#include "program.hh"

Program program_object;

Program::Program(){};
Program::~Program(){};
void Program::delete_all()
{
	for(auto it=proc_map.begin(); it != proc_map.end(); it++)
		delete it->second;
	command_options.remove_files();
};

void Program::set_procedure(Procedure * proc, int line)
{
	procedure = proc;
};
void Program::set_global_table(Symbol_Table & new_global_table)
{
	global_symbol_table = new_global_table;
	global_symbol_table.set_table_scope(global);
};

void Program::add_string(String_Ast * string_ast)
{
	if(string_ast != NULL)
		string_vars.push_back(string_ast);
}

void Program::print_string_vars(ostream & file_buffer)
{
	for(auto it = string_vars.begin(); it != string_vars.end(); it++)
		file_buffer << (*it)->get_label() << ":\t" << ".asciiz" << "\t\t" <<
			"\"" << (*it)->get_value() << "\"" << endl;
}


Symbol_Table_Entry & Program::get_symbol_table_entry(string variable)
{
	if(procedure != NULL && procedure->variable_in_symbol_list_check(variable))
		return procedure->get_symbol_table_entry(variable);
	else if(variable_in_symbol_list_check(variable))
		return global_symbol_table.get_symbol_table_entry(variable);
};

void Program::print_sym()
{
	procedure->print_sym(command_options.get_symtab_buffer());
};
void Program::print(){};

bool Program::variable_proc_name_check(string symbol)
{
	if(procedure == NULL)
		return false;
	return symbol.compare(procedure->get_proc_name()) == 0;

};
bool Program::variable_in_symbol_list_check(string variable)
{
	return global_symbol_table.variable_in_symbol_list_check(variable);
};
void Program::global_list_in_proc_check()
{
	global_symbol_table.global_list_in_proc_map_check();
};
bool Program::variable_in_proc_map_check(string symbol)
{
	for(auto it =  proc_map.begin(); it != proc_map.end(); it++)
	{
		if(symbol == it->first)
			return true;
	}
	return false;
};

void Program::add_procedure(Procedure * procedure, int line)
{
	if(procedure != NULL){
		string proc_name = procedure->get_proc_name();
		CHECK_INPUT_AND_ABORT(!(proc_map.count(proc_name)), "Overloading of the procedure is not allowed", line);
		proc_map[proc_name] =  procedure;
	}
}

bool Program::procedure_in_proc_map(string & proc_name)
{
	return proc_map.count(proc_name);
};

Procedure* Program::get_procedure(string proc_name)
{
	if(procedure_in_proc_map(proc_name))
		return proc_map[proc_name];
	return NULL;
}
