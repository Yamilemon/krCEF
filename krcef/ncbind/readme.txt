Title: �g���g���v���O�C�������l�C�e�B�u�N���X�o�C���_
Author: miahmie


������͉����H

������ C++ ���C�u������ TJS �ň������߂̃v���O�C����
�ȒP�ɍ�邱�Ƃ��ł���悤�ɂ��邽�߂� C++ �e���v���[�g�ł��B

�]���̃v���O�C���\�[�X�ł͈����̎󂯓n�������̃��b�p��
tp_stub.h �̃}�N�����g����ŏ����Ȃ���΂Ȃ�Ȃ������̂ł����C
�e���v���[�g�ɂ�肱����قƂ�ǃR���p�C���ɔC���邱�Ƃ��ł��܂��B

gcc 3.4 �n��� VC++2005 Express �œ���m�F���Ă��܂��B
�e���v���[�g�����̊֌W�� VC++6 �ł̓R���p�C�����疳�����Ǝv���܂��B
VC++2003 �⑼�̃R���p�C���͖��m�F�Ȃ̂łǂ��Ȃ邩�킩��܂���B


���ȒP�Ȑ���

�}�N���œo�^�������N���X�̒�`���L�q���邾���ł��B

#include "ncbind.hpp"
#include "�������C�u�����̃w�b�_��"

NCB_REGISTER_CLASS(�o�^����N���X��) {
  Constructor<�R���X�g���N�^�̈����̌^, ...>(0);
  Method("�o�^���郁�\�b�h��1", &Class::�o�^���郁�\�b�h1);
  Method("�o�^���郁�\�b�h��2", &Class::�o�^���郁�\�b�h2);
     :
  Method("�o�^���郁�\�b�h��n", &Class::�o�^���郁�\�b�hn);
}

�ڂ����� testbind.cpp �̃\�[�X������Ȃǂ��Ă��������B


���t�@�C���\��

  ncbind.hpp		���C���e���v���[�g
  ncbind.cpp		V2Link/V2Unlink ��`
  ncbind.def		gcc�p�G�N�X�|�[�g�t�@�C��
			VC++�ł� /EXPORT:V2Link /EXPORT:V2Unlink ���Ă�������
  ncb_invoke.hpp	�C�ӂ̃��\�b�h���ĂԂ��߂̃e���v���[�g
  ncb_foreach.h		�}�N����C�ӌ��W�J���邽�߂�include�}�N��

  testbind.*		�e�X�g�p�̃v���W�F�N�g


���ڍ�


�@��NCB_REGISTER_CLASS(Class) { ... }
�@��NCB_REGISTER_CLASS_DIFFER(Name, Class) { ... }

Class �� TJS�O���[�o�����(Name or Class)�ɓo�^���܂��B
NCB_REGISTER_CLASS �ł� Class ���CNCB_REGISTER_CLASS_DIFFER�ł� Name ��
�O���[�o����ԏ�ł̖��O�ƂȂ�܂��B�����N���X�̑��d�o�^�̓G���[�ɂȂ�܂��B


�� �ȑO�̃o�[�W������ NCB_{ CONSTRUCTOR, METHOD*, PROPERTY* } �}�N����
�@�g�p�ł��܂����CBridge�p�̃}�N���͗p�ӂ���Ă��܂���B

----------------------------------------------------------------
�@�@��Constructor();
�@�@��Constructor<arg1, arg2, ...>(0);

�����̌^�̃��X�g (arg1, arg2, ...) ��n���ăR���X�g���N�^��o�^���܂��B
����� (0) �� Constructor �̃I�[�o�[���[�h�p�̃V�O�l�`���Ƃ��ĕK�v�ł��B
�f�t�H���g�R���X�g���N�^�i�����Ȃ��j��o�^����ꍇ�͂��̌���ł͂���܂���B

�^�̈�v�����R���X�g���N�^�� TJS ���� new ����Ƃ��ɌĂ΂�܂��B
�o�^���Ȃ��ꍇ�͂��̃N���X�� new ����ƃG���[�ɂȂ�܂��B�i���܂��������j
�܂��C�I�[�o�[���[�h���ꂽ�����R���X�g���N�^�̓o�^�͂ł��܂���B
�ŏ��ɓo�^���ꂽ���̂��L���ƂȂ�܂��B�i���s���Ɍx�����b�Z�[�W���o�܂��j


----------------------------------------------------------------
�@�@��Factory(Class* (*)(iTJSDispatch2*[, arg1, arg2, ...]));
�@�@��Factory(tjs_error (TJS_INTF_METHOD *)(Class**, tjs_int, 
                                            tTJSVariant**, iTJSDispatch2*));

�C���X�^���X�𐶐�����֐����w�肵�ăR���X�g���N�^��o�^���܂��B
�P�Ԗڂ̈�����objthis���n��Proxy�̂悤�Ȋ֐����g�p������@�ƁC�����̌���
tTJSVariant�̔z���n��RawCallback�̂悤�Ȋ֐����g�p������@������܂��B

�O�҂͕Ԃ�l�Ƃ��Đ��������C���X�^���X�̃|�C���^��Ԃ��܂��B
�iNULL��Ԃ��ƃG���[�Ƃ��Ĉ����܂��j

��҂͈�Ԗڂ̈����ɃC���X�^���X�̃|�C���^�����������TJS_S_OK��Ԃ��܂��B
�iNULL���������񂾂�CTJS_S_OK�ȊO��Ԃ��ƃG���[�Ƃ��Ĉ����܂��j


----------------------------------------------------------------
�@�@��Method(Name, &Class::Method);

�N���X���\�b�h Method ��o�^���܂��BClass �� NCB_REGISTER_CLASS �ɂ�
�n���ꂽ�N���X�� typedef ����Ă��܂��B
Name �� TJS_W() �o�R�̃��C�h�����ł��C���L�q�̃i���[������ł����܂��܂���B
�i�i���[�̏ꍇ�͓o�^���Ɏ����I�ɕϊ���������܂��j

�I�[�o�[���[�h���œ������O�̃��\�b�h����������ꍇ��
���\�b�h�^�̎�������Ɏ��s����̂� static_cast �܂��� method_cast ��
�g�p���Ă��������B

�@�@static_cast<ReturnType (Class::*)(arg1, ... argN) [const]>(&Class::Method)
�@�@method_cast<ReturnType, Type, arg1, ... argN>(&Class::Method)

ReturnType �� ���\�b�h�̕Ԃ�l�̌^�ł��B
Type �̓N���X���\�b�h�̃^�C�v�ŁC
	Class	���ʂ̃N���X���\�b�h
	Const	const �ȃN���X���\�b�h�iReturnType Method(arg...) const;�j
	Static	static �ȃN���X���\�b�h
�� 3�̂����ǂꂩ���L�q���܂��B
arg1, ... argN �͈����̌^���w�肵�܂��B



----------------------------------------------------------------
�@�@��Method(Name, &Method, Proxy);

�N���X�O��static�֐����N���X���\�b�h�Ƃ��ĐU���킹��悤�o�^���܂��B
���̊֐��̈�Ԗڂ̈����͕K�����̃N���X�̃C���X�^���X�|�C���^�^�ɂ��܂��B
����� this �����̒l���n��CTJS����n�����c��̈����͂��̌�ɕ��ׂ܂��B

�����̃��C�u������o�^����Ƃ��ɁC���C�u�����Ɏ��������
���炩�̓���ȏ�������ꂽ���Ȃǂ̏ꍇ�ŗL���ł��B


----------------------------------------------------------------
�@�@��Method(Name, &Method, Bridge<BridgeFunctor>());

�u���b�W�t�@���N�^���w�肵�āC���̃N���X������ʂ̃N���X�C���X�^���X��
�������Ϗ����郁�\�b�h��o�^���܂��B
�t�@���N�^�͈ȉ��̂悤�Ȍ`���ł��B

struct BridgeFunctor { 
  BridgeClass* operator()(Class* p) const {
    return p->BridgeInstance;
  }
};
	Class          : �o�^���̃N���X
	BridgeClass    : �������Ϗ�����N���X
	BridgeInstance : Class���ɕێ�����Ă��� BridgeClass �̃C���X�^���X

Method�͈Ϗ���̃N���X�̃��\�b�h���L�q���܂��B
&Class::Method �ł͂Ȃ��C&BridgeClass::Method �Ƃ����\�L�ɂȂ�܂��B


----------------------------------------------------------------
�@�@��Method(Name, &Method, ProxyBridge<BridgeFunctor>());
�@�@��Method(Name, &Method, BridgeProxy<BridgeFunctor>());

Proxy���̃u���b�W�o�^�ł��B


----------------------------------------------------------------
�@�@��Property(Property, GetterMethod, SetterMethod);

Property �Ƃ������O�Ńv���p�e�B��o�^���܂��B
GetterMethod, SetterMethod �͂��ꂼ��
�v���p�e�B�擾�C�v���p�e�B�ݒ胁�\�b�h�ł��B
SetterMethod �܂��� GetterMethod �� 0 ��n���ƁC
���ꂼ�� �͓ǂݍ��ݐ�p�C�������ݐ�p�v���p�e�B�ɂȂ�܂��B

Setter/Getter�̃��\�b�h�^�̃`�F�b�N���Â��̂�
�w�肷�郁�\�b�h�ɂ͒��ӂ��Ă��������B

----------------------------------------------------------------
�@�@��Property(Property, GetterMethod, SetterMethod, Proxy);
�@�@��Property(Property, GetterMethod, SetterMethod, Bridge<Functor>());
�@�@��Property(Property, GetterMethod, SetterMethod, ProxyBridge<Functor>());
�@�@��Property(Property, GetterMethod, SetterMethod, BridgeProxy<Functor>());

Proxy/Bridge���̃v���p�e�B��o�^���܂��B
�ڍׂ� Method ���ڂ��Q�Ƃ��Ă��������B



----------------------------------------------------------------
�@�@��RawCallback(Name, &Callback, Flag);

�R�[���o�b�N���w�肵�� Name �Ƃ������O�Ń��\�b�h��o�^���܂��B
Callback �� tTJSNativeClassMethodCallback �^�� static �֐��|�C���^���C
�܂��́CtTJSNativeClassMethodCallback �̈����� iTJSDispatch2 *objthis ��
���̃N���X�̃C���X�^���X�̃|�C���^�ɂ������̂��g���܂��B
�i���̏ꍇ�C���ۂ̃l�C�e�B�u�C���X�^���X�ւ̃|�C���^�������Ƃ��ēn��܂��j

Flag �́C
	0		 (�ʏ�N���X���\�b�h��)
	TJS_STATICMEMBER (static���\�b�h��) 
�̂ǂ��炩���w��ł��܂��B

----------------------------------------------------------------
�@�@��RawCallback(Name, &GetterCallback, &SetterCallback, Flag);

�R�[���o�b�N�w��̃v���p�e�B�o�^�ł��B



----------------------------------------------------------------

�}�N�������̑����F


�@��NCB_ATTACH_CLASS(          Class, TJS2Class) { ... }
�@��NCB_ATTACH_CLASS_WITH_HOOK(Class, TJS2Class) { ... }

�g���g���Q�̊����̃N���X TJS2Class �� Class ��t�����܂��B
{ ... } �X�R�[�v���� NCB_REGISTER_CLASS �Ɠ����悤�ɒ�`���܂��B
�������C�R���X�g���N�^��` NCB_CONSTRUCTOR �͎g���܂���B

NCB_ATTACH_CLASS �œo�^�����ꍇ�CClass �̃C���X�^���X��
�o�^���ꂽ Class �̃��\�b�h�����߂ČĂ΂ꂽ�Ƃ���
�����Ȃ��̃R���X�g���N�^�� new ����C���\�b�h���Ă΂�܂��B

NCB_ATTACH_CLASS_WITH_HOOK �œo�^����ꍇ�́C���炩���ߌ�q��
NCB_GET_INSTANCE_HOOK ����`�ς݂łȂ���΂Ȃ�܂���B
Class �C���X�^���X�̐����̓t�b�N�p�N���X�Ɉ�C����܂��B


�@��NCB_GET_INSTANCE_HOOK(Class) { ... };
�@�@��NCB_GET_INSTANCE_HOOK_CLASS
�@�@��NCB_INSTANCE_GETTER(ObjThis)

TJS ����l�C�e�B�u�N���X Class �̃��\�b�h���Ăяo������
�C���X�^���X���擾����֐����t�b�N�i�Ƃ������Ē�`�j���܂��B
�ڂ����� testbind.cpp �\�[�X���Q�Ƃ��Ă��������B

NCB_ATTACH_CLASS �����łȂ��CNCB_REGISTER_CLASS ��
�o�^�����N���X�ɂ��K�p����܂��B

�܂��C���ׂẴN���X���\�b�h�ɓK�p����邽�߁C
�w��̌ʃ��\�b�h�Ƀt�b�N���铙�͂ł��܂���B
�@�˗v�]������Ύ������܂�


�@��NCB_REGISTER_SUBCLASS(Class)
�@�@��SubClass(Name, TypeWrap<Class>());

�T�u�N���X�̒�`�Ɠo�^�ł��B�N���X����static�Ƃ��ăT�u�N���X���u����܂��B
������g�����ƂŖ��O��Ԃ��������ɊK�w�\�����Ƃ邱�Ƃ��ł��܂��B
���������R�[�h�ɂ��s������邩������܂���


�@��NCB_REGISTER_FUNCTION(Name, Function);

TJS �O���[�o����Ԃ� Name �Ƃ������O�� Function �Ƃ����֐���o�^���܂��B
Function �� tTJSNativeClassMethodCallback �^�̏ꍇ��
���̂܂� RawCallback �`���̃O���[�o���֐��Ƃ��ē��삵�܂��B


�@��NCB_ATTACH_FUNCTION(Name, TJS2Class, Function);

�g���g���Q�̊����̃N���X TJS2Class �� Name �Ƃ������O��
Function ��t�����܂��BFunction �� tTJSNativeClassMethodCallback �^�̏ꍇ��
���̂܂܃��\�b�h�� RawCallback �Ɠ����悤�ɓ��삵�܂��B

���̃}�N���ł́C�� static �Ȋ֐������t���ł��܂���Bstatic �ȃ��\�b�h�Ƃ���
�o�^�������ꍇ�́C�_�~�[�� static ���\�b�h�������݂��Ȃ��N���X�����C
NCB_ATTACH_CLASS �œo�^���Ă��������B�istatic ���\�b�h�̌Ăяo���ł����
�l�C�e�B�u�C���X�^���X�͐�������܂���j



�@��NCB_REGISTER_INSTANCE(...); // ������

�@�@�� �Q�Ƃ�Ԃ� function / property �ő�p�ł��܂�


�@��NCB_TYPECONV_CAST(Type, CastType);

�����̌^�� Type �̏ꍇ�C�L���X�g CastType ���w�肵��
tTJSVariant �Ƒ��ݕϊ�����悤�ɓo�^���܂��B

�@��NCB_SET_CONVERTOR(Type, Convertor);

�����̌^ Type ��ϊ�����N���X��o�^���܂��B
�ڂ����� ncbind.hpp �̃R�����g�����Q�Ƃ��Ă��������B



�@��NCB_PRE_REGIST_CALLBACK(Callback);
�@��NCB_POST_REGIST_CALLBACK(Callback);
�@��NCB_PRE_UNREGIST_CALLBACK(Callback);
�@��NCB_POST_UNREGIST_CALLBACK(Callback);

�N���X��o�^�E�J������O��ɌĂ΂��R�[���o�b�N void Callback() ��
�o�^���܂��B�Ă΂�鏇�Ԃ͈ȉ��̂Ƃ���ł��B

V2Link���F
	PRE_REGIST_CALLBACK
	�N���X�o�^
	POST_REGIST_CALLBACK
V2Unlink���F
	PRE_UNREGIST_CALLBACK
	�N���X�J��
	POST_UNREGIST_CALLBACK

������ނ̃R�[���o�b�N�������o�^���ꂽ�ꍇ�̏��Ԃ̕ۏ؂͂���܂���B



������

�E�p���֌W�̓T�|�[�g���Ă��Ȃ�
�@�ˌp���֌W�ɂ���N���X���m��o�^�����ꍇ�C�ʂ̃N���X�����ɂȂ�
	�Einstanceof �Ŕh���N���X�C���X�^���X�̃`�F�b�N���ł��Ȃ�
	�E�����ɔh���N���X�C���X�^���X��n�����ꍇ��
	�@�C���X�^���X�|�C���^���擾�ł����ɃG���[�ƂȂ�

�E�����̏ȗ��ɂ��f�t�H���g�l���T�|�[�g���Ă��Ȃ�
�@��TJS����n�������̌��̓��\�b�h�̈����̌��ȏ�ł��邱��
�@�@�]���ɓn���ꂽ�����͖�������C����Ȃ��ꍇ�� TJS_E_BADPARAMCOUNT ���Ԃ�
�@�ˉϒ��������T�|�[�g����ꍇ�� RawCallback �Ŏ��͎������邱��

�Enamespace ���ł̃N���X�o�^�͍l�����Ă��Ȃ��̂� namespace �O�ōs������
�@��namespace ���̃N���X��o�^����ꍇ�� typedef ����Ȃǂ�
�@�@�K�� namespace �̊O�ōs�� (:: ���܂ނƃG���[�ɂȂ�)

  ex.
	typedef ::Foo::Bar::TargetClass TargetClass;

	NCB_REGISTER_CLASS(TargetClass) { ... }


�E�R���X�g���N�^�͂P�����L�q�ł��Ȃ�
�@�˃C���X�^���X�𐶐����� static �ȃ��\�b�h�������Ȃǂ��ĉ�������

�E�o�^�����N���X�̃C���X�^���X�����\�b�h�̕Ԃ�l�ŕԂ����ɂ͒��ӂ��K�v
�@�˃C���X�^���X�̑��d delete ��C���� delete ����Ă��閳����
�@�@�C���X�^���X���g�p�����\��������

�R�s�[�ŕԂ��@�F�R�s�[�R���X�g���N�^�ŐV���ȃC���X�^���X����������TJS���֕Ԃ�
�Q�ƂŕԂ��@�@�F���̂܂�TJS���֕Ԃ���Cinvalidate ���� delete ����Ȃ�
�|�C���^�ŕԂ��F���̂܂�TJS���֓n����Cinvalidate ���� delete �����
const �̎Q��/�|�C���^�͋����I�� const ���������


�E�Q�ƂŒl�����������ĕԂ��悤�ȃ��\�b�h�ɂ͑Ή��ł��Ȃ�
�@�˓K����RawCallback�֐��������Ȃǂ��đΏ����邱��

�ETJSCreateNativeClassMethod ���g�킸�Ƀ��\�b�h�Ăяo����Ǝ�����
�@���Ă��邽�߁C�����ɂ킽��\�[�X�݊����ۂĂ�Ƃ����ۏ؂��Ȃ�
�@�ˋg���g���Q���̂��������e�t�F�[�Y������ʂɂ����c��ˁH


���Ƃ茾

�E�e���v���[�g�� Modern C++ Design ���Ђ�ǂ񂾂��炢�ŁCBoost�Ƃ����
�@ncb_invoke�̑O�g�o�[�W������TypeList�Ŏ��������������������
�@�����܂ł���悤�ȕ��ł͂Ȃ��ƌ�����̂ō���͗͋ƂŎ���

�EtTJSVariantType tTJSVariant::Type() �͉��� const ���\�b�h�łȂ��̂�
�@const_cast�g���n���ɂȂ��Ĕs�k�C��
	�ˏC������܂������C�]���݊��d���̂��ߌ��ǎg���Ȃ��i�܁j



��TODO����

�Encibind.hpp �Â��R�����g�̐���
�ENCB_SET_CONVERTOR �e�X�g
�EAttach���Ɋ����̃��\�b�h���������ꍇ�̏���
�E�I�[�o�[���[�h�ƈ����̏ȗ����T�|�[�g���邩�H
