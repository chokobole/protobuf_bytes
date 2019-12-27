import os
import platform
import setuptools

py_version = platform.python_version_tuple()
if py_version[0] == '3' and py_version < ('3', '5'):
  raise RuntimeError('Python version 3.5+ is required.')

_README_PATH = os.path.join(
    os.path.dirname(os.path.realpath(__file__)), 'README.md')
with open(_README_PATH, 'rb') as fp:
  LONG_DESCRIPTION = fp.read().decode('utf-8')

setuptools.setup(
    name='protobuf_bytes',
    version='0.0.1',
    author='Wonyong Kim',
    author_email='chokobole33@gmail.com',
    description='Python implementation of protobuf_bytes',
    long_description=LONG_DESCRIPTION,
    long_description_content_type='text/markdown',
    url='https://github.com/chokobole/protobuf_bytes',
    packages=setuptools.find_packages(exclude = [
        'test',
    ]),
    install_requires=['protobuf'],
    license='BSD-3-Clause',
    classifiers=[
        'Programming Language :: Python',
        'Programming Language :: Python :: 3',
        'Programming Language :: Python :: 3.5',
        'Programming Language :: Python :: 3.6',
        'Programming Language :: Python :: 3.7',
        'Intended Audience :: Developers',
        'License :: OSI Approved :: BSD License',
        'Topic :: Software Development :: Libraries :: Python Modules',
        'Operating System :: OS Independent',
    ],
)
