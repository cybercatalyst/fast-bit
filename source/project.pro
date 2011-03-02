TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS = backend \
          kernel \
          frontend

# Application must be last in order.
SUBDIRS += application
