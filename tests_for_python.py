import os
import subprocess

import files
import function
import functions
import modules
import pythonfiles

# komenda do urtuchumienia testow dla pythona w cmd , wymaga pytesta i roziwiniecie cov
# pytest test_for_python.py --cov


'''testy dla czesci projektu w pythonie '''


def test_counting_lines_of_code():
    path = r'.\\'
    with open(path + '\\' + 'test_file.txt', 'w') as test_file:
        test_file.write("this text file should have 2 lines\n")
        test_file.write('exactly 2 lines')
        test_file.close()
    expected_value = 2

    result = functions.counting_lines_of_code('test_file.txt')
    os.remove('./test_file.txt')
    assert result == expected_value


def test_write_to_file_fun_data():
    test_list_1 = [1, 2]
    test_list_2 = [2, 3]
    result = ['-1', '0']

    resultlist = functions.write_to_file_fun_data(test_list_1, test_list_2)

    assert resultlist == result


# def test_write_to_file():
# random_list=['wiktor','wanat']
# # path_2=r'C:\Users\WIKUS\PycharmProjects\Project_IO\test.txt'
# # RegistrationClass.Registration.write_to_file(random_list)
# # with open(path_2,'r') as file_to_read:
# #    for line in file_to_read:
# #       List=file_to_read.read()
# # assert random_list==List

# TEST DLA PYTHON_FILES
def test_of_file_searching():
    File_of_code = pythonfiles.FileInDirectory()
    resultexpected = ['temp.dot']

    result = pythonfiles.FileInDirectory.list_directory(File_of_code, './', 'dot')

    assert result == resultexpected


# tests for function
def test_checking_connections_between_functions_one():
    data_list = ['pythonfiles.py']
    result_expected = ['list_directory']

    result = function.Functions.checking_connections_between_functions1(data_list)

    assert result == result_expected


def test_checking_weight_of_connections_between_functions():
    data_list = ['pythonfiles.py']
    function_of_python_files_py = ['list_directory']
    result_exp = ['list_directory']
    Class_object = function.Functions()  # createing object of this specific class

    result = function.Functions.checking_weight_of_connections_between_functions(Class_object, data_list,
                                                                                 function_of_python_files_py)

    assert result == result_exp


def test_checking_connections_between_function():
    pass


# tests for files
def test_checking_weight_of_connections_between_files():
    with open('./one.py', 'w') as file_1:
        file_1.write('import wo' + '\n')
        file_1.write('wo.function()')
        file_1.close()
    with open('./wo.py', 'w') as file_2:
        file_2.write('def function():pass')
        file_2.close()
    result_expected = 1

    result_of_function = files.Files.checking_weight_of_connections_between_files('one.py', 'wo')
    os.remove("one.py")
    os.remove("wo.py")

    assert result_of_function == result_expected


# troche syf to testowanie bo ta funkcja jest lawacka
def test_checking_connections_between_files():
    temporary_file_list = []
    with open('./3.py', 'w') as file_3:
        file_3.write('elo')
        file_3.close()
    with open('./4.py', 'w') as file_4:
        file_4.write('import 1')
        file_4.close()

    result_expected = None  # 2 non existing files so can't be connectec

    result_of_function_checking_connection_of_file = files.Files.checking_connections_between_files(temporary_file_list)

    os.remove('3.py')
    os.remove('4.py')

    assert result_of_function_checking_connection_of_file == result_expected


# test for modules
def test_searching_for_used_modules():
    files = []
    with open('./5.py', 'w') as try_file:
        try_file.write('import time')
        try_file.close()
    result_expected = ['time']
    files.append('5.py')

    result_of_function = modules.Modules.searching_for_used_modules(files)
    os.remove('5.py')
    assert result_of_function == result_expected


def test_checking_connections_between_modules():
    filess = []
    with open('./66.py', 'w') as try_files:
        try_files.write('elko:\n')
        try_files.write('\tpass')
        try_files.close()

    modul_list = ['time']
    filess.append('66.py')
    result_expectedd = None

    result_of_function = modules.Modules.checking_connections_between_modules(filess, modul_list)
    os.remove('66.py')
    assert result_of_function == result_expectedd


def authomatic_testes():
    cmd_command = 'cd C:\\Users\\WIKUS\\PycharmProjects\\IO-ProjectJozin\\ && pytest tests_for_python.py --cov > result_of_tests.txt"'
    proc = subprocess.call(cmd_command, shell=True)
    return True
