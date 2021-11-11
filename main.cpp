#include <Windows.h>
#include <comdef.h>
#include <objidl.h>
#include <tchar.h>
#include <stdio.h>

int _tmain(int argc, TCHAR** argv) {
	if (argc < 2) {
		_tprintf(_T("ValidateCompoundFile test.msg\n"));
		return 1;
	}
	IStoragePtr pStorage;
	HRESULT hr;
	hr = StgOpenStorageEx(
		argv[1],
		STGM_READ | STGM_SHARE_DENY_WRITE,
		STGFMT_STORAGE,
		0,
		nullptr,
		nullptr,
		IID_IStorage,
		reinterpret_cast<void**>(&pStorage)
	);
	_tprintf(_T("StgOpenStorageEx returned 0x%08x\n"), hr);
	if (hr == STG_E_DOCFILECORRUPT) {
		return 2;
	}
	if (FAILED(hr)) {
		return 1;
	}
	return 0;
}