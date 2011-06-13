
$: << './tools/rake_build_system' #make sure this rakefile can see all the build system files

ENV['BOOST_VERSION']='boost_1_46_1'

require 'rake/clean'
CLOBBER.include('doc')					# remove any doxygen-generated files

require 'rake.environment.rb'           # this sets up a slew of environment constants
require 'plugins/rake.cpp.rb'           # this provides the facilities for declaring C++ style builds
require 'plugins/rake.boost.rb'         # provides location and names of the boost libraries
require 'plugins/rake.swigjava.rb'      # provides helpers for creating cpp/java bindings using swig
require 'plugins/rake.source.rb'        # provides licensing helpers

DEFAULT_INCLUDES << __FILE__.pathmap('%d')

#format is name => options, :dir is required
$projects = {
:apl => {:dir => 'APL' },
:testapl => {:dir => 'TestAPL'},
:apltesttools => {:dir => 'APLTestTools'},
:dnp3 => {:dir => 'DNP3'},
:dnp3xml => {:dir => 'DNP3XML'},
:xmlbindings => {:dir => 'XMLBindings'},
:dnp3test => {:dir => 'DNP3Test'},
:testset => {:dir => 'TestSet'},
:slavedemo => {:dir => 'SlaveDemo'},
:tinyxml => {:dir => 'tinyxml'},
:aplxml => {:dir => 'APLXML'},
:terminal => {:dir => 'Terminal'},
:terminaltest => {:dir => 'TerminalTest'},
#:dnp3java => {:dir => 'DNP3Java'},
}

add_projects($projects) #removes projects that are not valid for $hw_os

SOURCE_PROJECTS = [:apl, :testapl, :apltesttools, :dnp3, :dnp3test, :dnp3xml, :aplxml, :testset]
SOURCE_DIRS = SOURCE_PROJECTS.collect { |p| $projects[p][:dir] }

desc 'Generate doxygen html docs for the project'
task :document do
  `doxygen ./config/doxygen.config`
end

desc 'Generate a sloccount report for the project'
task :sloccount do
  dirs = SOURCE_DIRS + ['tools/rake_build_system']
  `sloccount --wide --details #{dirs.join(' ')} > sloccount.sc`
end

desc 'Formats all of the C++ h/cpp files with uncrustify'
format_dirs = ['DNP3', 'APL', 'DNP3Test', 'TestAPL', 'APLTestTools', 'Terminal', 'TerminalTest', 'SlaveDemo']
task :format do
  format_dirs.each do |dir|
   cmd = "astyle --options=config/astyle.cfg #{dir}/*.cpp #{dir}/*.h"
   puts cmd
   `#{cmd}`   
  end
end

namespace :license do

  license_dirs = SOURCE_DIRS << 'External\build_system'
  
  license_types = {
    :cpp => {:exts => ['.cpp','.h'], :comment => '// '},
    :ruby => {:exts => ['.rb'], :comment => '# '},
  }

  extensions = license_types.collect { |k,v| v[:exts] }.join('/')
  
  desc "add the licensing file to all #{extensions}"
  task :add do
    license_types.each { |key,options| add_license(license_dirs, options, 'FILE_LICENSE') }
  end

  desc "remove the licensing file from all #{extensions}"
  task :remove do
    license_types.each { |key,options| remove_license(license_dirs, options, 'FILE_LICENSE') }
  end
  
end
