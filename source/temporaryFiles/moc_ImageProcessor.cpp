/****************************************************************************
** Meta object code from reading C++ file 'ImageProcessor.h'
**
** Created: Fri Mar 4 20:10:56 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../headerFiles/ImageProcessor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ImageProcessor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ImageProcessor[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      34,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      24,   16,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      56,   15,   40,   15, 0x0a,
      82,   67,   15,   15, 0x0a,
     130,   67,   15,   15, 0x0a,
     180,   67,   15,   15, 0x0a,
     229,   67,   15,   15, 0x0a,
     272,   67,   15,   15, 0x0a,
     322,   67,   15,   15, 0x0a,
     380,  367,   15,   15, 0x0a,
     412,  367,   15,   15, 0x0a,
     439,  367,   15,   15, 0x0a,
     468,  367,   15,   15, 0x0a,
     496,  367,   15,   15, 0x0a,
     528,  367,   15,   15, 0x0a,
     569,  552,   15,   15, 0x0a,
     617,  600,   15,   15, 0x0a,
     649,  367,   15,   15, 0x0a,
     697,  367,   15,   15, 0x0a,
     728,  367,   15,   15, 0x0a,
     757,  367,   15,   15, 0x0a,
     788,  367,   15,   15, 0x0a,
     825,  367,   15,   15, 0x0a,
     855,  367,   15,   15, 0x0a,
     878,  367,   15,   15, 0x0a,
     939,  909,   15,   15, 0x0a,
     967,  909,   15,   15, 0x0a,
    1000,  909,   15,   15, 0x0a,
    1037,  909,   15,   15, 0x0a,
    1089, 1068,   15,   15, 0x0a,
    1139, 1120,   15,   15, 0x0a,
    1181, 1120,   15,   15, 0x0a,
    1243, 1221,   15,   15, 0x0a,
    1301, 1277,   15,   15, 0x0a,
    1341,  367,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ImageProcessor[] = {
    "ImageProcessor\0\0message\0status(QString)\0"
    "ImageProcessor*\0instance()\0image,renderer\0"
    "normalizedRedValueDistribution(QImage,QObject*)\0"
    "normalizedGreenValueDistribution(QImage,QObject*)\0"
    "normalizedBlueValueDistribution(QImage,QObject*)\0"
    "normalizedHueDistribution(QImage,QObject*)\0"
    "normalizedSaturationDistribution(QImage,QObject*)\0"
    "normalizedValueDistribution(QImage,QObject*)\0"
    "sender,image\0autoBrightness(QObject*,QImage)\0"
    "redFilter(QObject*,QImage)\0"
    "greenFilter(QObject*,QImage)\0"
    "blueFilter(QObject*,QImage)\0"
    "grayValueSplay(QObject*,QImage)\0"
    "invert(QObject*,QImage)\0sender,image,thr\0"
    "threshold(QObject*,QImage,int)\0"
    "sender,image,bgt\0brightness(QObject*,QImage,int)\0"
    "symmetricDifferentiationFilter(QObject*,QImage)\0"
    "prewittFilter(QObject*,QImage)\0"
    "sobelFilter(QObject*,QImage)\0"
    "laPlaceFilter(QObject*,QImage)\0"
    "kirschCompassFilter(QObject*,QImage)\0"
    "makeAbsolute(QObject*,QImage)\0"
    "erode(QObject*,QImage)\0"
    "convertToGray(QObject*,QImage)\0"
    "sender,firstImage,secondImage\0"
    "add(QObject*,QImage,QImage)\0"
    "subtract(QObject*,QImage,QImage)\0"
    "multiplicate(QObject*,QImage,QImage)\0"
    "divide(QObject*,QImage,QImage)\0"
    "sender,image,degrees\0"
    "rotate(QObject*,QImage,double)\0"
    "sender,image,loops\0"
    "fillUpHorizontalGaps(QObject*,QImage,int)\0"
    "fillUpVerticalGaps(QObject*,QImage,int)\0"
    "sender,image,stepping\0"
    "reduceColors(QObject*,QImage,int)\0"
    "sender,image,colorValue\0"
    "removeColorByValue(QObject*,QImage,int)\0"
    "detectZeroCrossings(QObject*,QImage)\0"
};

const QMetaObject ImageProcessor::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ImageProcessor,
      qt_meta_data_ImageProcessor, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ImageProcessor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ImageProcessor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ImageProcessor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ImageProcessor))
        return static_cast<void*>(const_cast< ImageProcessor*>(this));
    return QObject::qt_metacast(_clname);
}

int ImageProcessor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: status((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: { ImageProcessor* _r = instance();
            if (_a[0]) *reinterpret_cast< ImageProcessor**>(_a[0]) = _r; }  break;
        case 2: normalizedRedValueDistribution((*reinterpret_cast< QImage(*)>(_a[1])),(*reinterpret_cast< QObject*(*)>(_a[2]))); break;
        case 3: normalizedGreenValueDistribution((*reinterpret_cast< QImage(*)>(_a[1])),(*reinterpret_cast< QObject*(*)>(_a[2]))); break;
        case 4: normalizedBlueValueDistribution((*reinterpret_cast< QImage(*)>(_a[1])),(*reinterpret_cast< QObject*(*)>(_a[2]))); break;
        case 5: normalizedHueDistribution((*reinterpret_cast< QImage(*)>(_a[1])),(*reinterpret_cast< QObject*(*)>(_a[2]))); break;
        case 6: normalizedSaturationDistribution((*reinterpret_cast< QImage(*)>(_a[1])),(*reinterpret_cast< QObject*(*)>(_a[2]))); break;
        case 7: normalizedValueDistribution((*reinterpret_cast< QImage(*)>(_a[1])),(*reinterpret_cast< QObject*(*)>(_a[2]))); break;
        case 8: autoBrightness((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QImage(*)>(_a[2]))); break;
        case 9: redFilter((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QImage(*)>(_a[2]))); break;
        case 10: greenFilter((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QImage(*)>(_a[2]))); break;
        case 11: blueFilter((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QImage(*)>(_a[2]))); break;
        case 12: grayValueSplay((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QImage(*)>(_a[2]))); break;
        case 13: invert((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QImage(*)>(_a[2]))); break;
        case 14: threshold((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QImage(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 15: brightness((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QImage(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 16: symmetricDifferentiationFilter((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QImage(*)>(_a[2]))); break;
        case 17: prewittFilter((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QImage(*)>(_a[2]))); break;
        case 18: sobelFilter((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QImage(*)>(_a[2]))); break;
        case 19: laPlaceFilter((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QImage(*)>(_a[2]))); break;
        case 20: kirschCompassFilter((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QImage(*)>(_a[2]))); break;
        case 21: makeAbsolute((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QImage(*)>(_a[2]))); break;
        case 22: erode((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QImage(*)>(_a[2]))); break;
        case 23: convertToGray((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QImage(*)>(_a[2]))); break;
        case 24: add((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QImage(*)>(_a[2])),(*reinterpret_cast< QImage(*)>(_a[3]))); break;
        case 25: subtract((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QImage(*)>(_a[2])),(*reinterpret_cast< QImage(*)>(_a[3]))); break;
        case 26: multiplicate((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QImage(*)>(_a[2])),(*reinterpret_cast< QImage(*)>(_a[3]))); break;
        case 27: divide((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QImage(*)>(_a[2])),(*reinterpret_cast< QImage(*)>(_a[3]))); break;
        case 28: rotate((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QImage(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 29: fillUpHorizontalGaps((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QImage(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 30: fillUpVerticalGaps((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QImage(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 31: reduceColors((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QImage(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 32: removeColorByValue((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QImage(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 33: detectZeroCrossings((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QImage(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 34;
    }
    return _id;
}

// SIGNAL 0
void ImageProcessor::status(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
