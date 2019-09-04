import codecs
import glob
import os
import sys
import setuptools  # must import before Extension
from distutils.core import setup, Extension

# source file
source_root = "src"
sources = list()
sources += glob.glob(os.path.join(source_root, "*.c"))

# exclude
exclude = []
sources = [s for s in sources if s not in exclude]
print(sources)

# include file;
includes = [
    'src/'
]

# extra args
extra_compile_args = []
if sys.platform == 'win32':
    extra_compile_args += ['/DNOMINMAX', '/DBOOST_PYTHON_SOURCE', '/DBOOST_PYTHON_STATIC_LIB', '/DBOOST_ALL_NO_LIB',
                           '/D_WINDOWS', '/EHsc']
elif sys.platform == 'darwin':
    os.environ['CC'] = 'clang++'
    os.environ['CXX'] = 'clang++'
    extra_compile_args += []
else:
    extra_compile_args += []

if not 'MACOSX_DEPLOYMENT_TARGET' in os.environ:
    os.environ['MACOSX_DEPLOYMENT_TARGET'] = '10.12'

pyseg_module = Extension(
    name='pyseg',
    include_dirs=includes,
    sources=sources,
    extra_compile_args=extra_compile_args
)

pkg_name = 'pyseg'
setup(
    name=pkg_name,
    version='0.0.9',
    description='sentence seg module written in C',
    long_description=codecs.open('README.md', encoding='utf-8').read(),
    author='wbq813',
    author_email='wbq813@foxmail.com',
    url='https://github.com/wbq813/pyseg',
    license='MIT',
    platforms='linux',
    classifiers=[
        'Development Status :: 4 - Beta',
        'Intended Audience :: Developers',
        'Intended Audience :: Science/Research',
        'License :: OSI Approved :: MIT License',
        'Programming Language :: Python :: 3.5',
        'Programming Language :: Python :: 3.6',
        "Topic :: Software Development",
        "Topic :: Software Development :: Libraries :: Python Modules",
        "Topic :: Scientific/Engineering",
        "Topic :: Scientific/Engineering :: Information Analysis",
        "Topic :: Text Processing :: Linguistic",
    ],
    packages=setuptools.find_packages(),
    # include_package_data=True,
    # lexion file, seams useless
    package_data={'lexicon': ['*.lex', '*.ini']},
    zip_safe=False,
    python_requires='>=3.5',
    ext_modules=[pyseg_module], )
