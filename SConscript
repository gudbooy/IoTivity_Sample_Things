#******************************************************************
#
# Copyright 2014 Intel Mobile Communications GmbH All Rights Reserved.
#
#-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
#-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

##
# Examples build script
##
thread_env = SConscript('#build_common/thread.scons')
lib_env = thread_env.Clone()

# Add third party libraries
SConscript('#resource/third_party_libs.scons', 'lib_env')
examples_env = lib_env.Clone()
target_os = examples_env.get('TARGET_OS')
######################################################################
# Build flags
######################################################################
examples_env.AppendUnique(CPPPATH = [
		'../../include/',
		'../../csdk/stack/include',
		'../../c_common/ocrandom/include',
		'../../csdk/logger/include',
		'../../oc_logger/include',
		'./'
		])

examples_env.AppendUnique(LIBPATH = [examples_env.get('BUILD_DIR')])
examples_env.AppendUnique(RPATH = [examples_env.get('BUILD_DIR')])
examples_env.PrependUnique(LIBS = ['coap'])
examples_env.AppendUnique(LIBS = ['connectivity_abstraction'])
examples_env.AppendUnique(LIBS = ['oc_logger'])
examples_env.AppendUnique(LIBS = ['octbstack'])
examples_env.AppendUnique(LIBS = ['oc'])

compiler = examples_env.get('CXX')
if 'g++' in compiler:
	examples_env.AppendUnique(CXXFLAGS = ['-std=c++0x', '-Wall'])

if target_os in ['msys_nt', 'windows']:
	examples_env.PrependUnique(LIBS = ['mswsock', 'ws2_32', 'iphlpapi', 'ole32'])

if examples_env.get('SECURED') == '1':
	examples_env.AppendUnique(LIBS = ['tinydtls'])
	examples_env.AppendUnique(CPPDEFINES = ['_WITH_DTLS_'])
	if target_os in ['msys_nt', 'windows']:
		examples_env.AppendUnique(LIBS = ['advapi32'])

if target_os == 'android':
	examples_env.AppendUnique(CXXFLAGS = ['-frtti', '-fexceptions'])
	examples_env.AppendUnique(LIBS = ['gnustl_shared'])

	if not examples_env.get('RELEASE'):
		examples_env.AppendUnique(LIBS = ['log'])

if target_os in ['darwin', 'ios']:
	examples_env.AppendUnique(CPPDEFINES = ['_DARWIN_C_SOURCE'])

if examples_env.get('LOGGING'):
	examples_env.AppendUnique(CPPDEFINES = ['TB_LOG'])

if examples_env.get('WITH_CLOUD'):
	examples_env.AppendUnique(CPPDEFINES = ['WITH_CLOUD'])

if target_os in ['msys_nt', 'windows']:
	examples_env.AppendUnique(LIBS = ['Comctl32', 'Gdi32', 'User32'])

if examples_env.get('LOGGING'):
	examples_env.AppendUnique(CPPDEFINES = ['TB_LOG'])

if 'CLIENT' in examples_env.get('RD_MODE'):
	examples_env.AppendUnique(CPPDEFINES = ['RD_CLIENT'])

def make_single_file_cpp_program(program_name):
	return examples_env.Program(program_name, ['main.cpp', 'simple_server_temp.cpp', 
			'resourceImpl.cpp', 'simple_server_humidity.cpp',
			'simple_server_fan.cpp', 'simple_server_light.cpp'])

######################################################################
# Source files and Targets
######################################################################
example_names = [
	'test'
	]
#example_env.Program('test', ['main.cpp', 'simple_server_temp.cpp'])

examples = map(make_single_file_cpp_program, example_names)
