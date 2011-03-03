TEMPLATE = subdirs

CONFIG += ordered

CONFIG -= flat

SUBDIRS = backend \
          frontend \
          kernel \
	  kernel/extensions

# Application must be last in order.
SUBDIRS += application

backend.subdir = backend
backend.depends =

kernel.subdir = kernel
kernel.depends =

frontend.subdir = frontend
frontend.depends =

application.subdir = application
application.depends = backend kernel frontend
