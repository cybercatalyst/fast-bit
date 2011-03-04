/****************************************************************************
** Meta object code from reading C++ file 'ImageOpenGLRenderer.h'
**
** Created: Fri Mar 4 20:11:06 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../headerFiles/renderers/ImageOpenGLRenderer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ImageOpenGLRenderer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ImageOpenGLRenderer[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x05,

 // slots: signature, parameters, type, tag, flags
      36,   20,   20,   20, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_ImageOpenGLRenderer[] = {
    "ImageOpenGLRenderer\0\0historyEmpty()\0"
    "updateAnimations()\0"
};

const QMetaObject ImageOpenGLRenderer::staticMetaObject = {
    { &OpenGLRenderer::staticMetaObject, qt_meta_stringdata_ImageOpenGLRenderer,
      qt_meta_data_ImageOpenGLRenderer, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ImageOpenGLRenderer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ImageOpenGLRenderer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ImageOpenGLRenderer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ImageOpenGLRenderer))
        return static_cast<void*>(const_cast< ImageOpenGLRenderer*>(this));
    return OpenGLRenderer::qt_metacast(_clname);
}

int ImageOpenGLRenderer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = OpenGLRenderer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: historyEmpty(); break;
        case 1: updateAnimations(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void ImageOpenGLRenderer::historyEmpty()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
