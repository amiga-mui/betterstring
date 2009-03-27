/* Automatically generated header! Do not edit! */

#ifndef _INLINE_MUIMASTER_H
#define _INLINE_MUIMASTER_H

#ifndef AROS_LIBCALL_H
#include <aros/libcall.h>
#endif /* !AROS_LIBCALL_H */

#ifndef MUIMASTER_BASE_NAME
#define MUIMASTER_BASE_NAME MUIMasterBase
#endif /* !MUIMASTER_BASE_NAME */

#define MUI_NewObjectA(___par1, ___last) __MUI_NewObjectA_WB(MUIMASTER_BASE_NAME, ___par1, ___last)
#define __MUI_NewObjectA_WB(___base, ___par1, ___last) \
	AROS_LC2(Object *, MUI_NewObjectA, \
	AROS_LCA(CONST_STRPTR, (___par1), A0), \
	AROS_LCA(struct TagItem *, (___last), A1), \
	struct Library *, (___base), 5, Muimaster)

#ifndef NO_INLINE_STDARG
#define MUI_NewObject(___par1, ___last, ...) __MUI_NewObject_WB(MUIMASTER_BASE_NAME, ___par1, ___last, ## __VA_ARGS__)
#define __MUI_NewObject_WB(___base, ___par1, ___last, ...) \
	({IPTR _tags[] = { (IPTR) ___last, ## __VA_ARGS__ }; __MUI_NewObjectA_WB((___base), (___par1), (struct TagItem *) _tags); })
#endif /* !NO_INLINE_STDARG */

#define MUI_DisposeObject(___last) __MUI_DisposeObject_WB(MUIMASTER_BASE_NAME, ___last)
#define __MUI_DisposeObject_WB(___base, ___last) \
	AROS_LC1NR(VOID, MUI_DisposeObject, \
	AROS_LCA(Object *, (___last), A0), \
	struct Library *, (___base), 6, Muimaster)

#define MUI_RequestA(___par1, ___par2, ___par3, ___par4, ___par5, ___par6, ___last) __MUI_RequestA_WB(MUIMASTER_BASE_NAME, ___par1, ___par2, ___par3, ___par4, ___par5, ___par6, ___last)
#define __MUI_RequestA_WB(___base, ___par1, ___par2, ___par3, ___par4, ___par5, ___par6, ___last) \
	AROS_LC7(LONG, MUI_RequestA, \
	AROS_LCA(APTR, (___par1), D0), \
	AROS_LCA(APTR, (___par2), D1), \
	AROS_LCA(LONGBITS, (___par3), D2), \
	AROS_LCA(CONST_STRPTR, (___par4), A0), \
	AROS_LCA(CONST_STRPTR, (___par5), A1), \
	AROS_LCA(CONST_STRPTR, (___par6), A2), \
	AROS_LCA(APTR, (___last), A3), \
	struct Library *, (___base), 7, Muimaster)

#ifndef NO_INLINE_VARARGS
#define MUI_Request(___par1, ___par2, ___par3, ___par4, ___par5, ___par6, ___tag1, ...) __MUI_Request_WB(MUIMASTER_BASE_NAME, ___par1, ___par2, ___par3, ___par4, ___par5, ___par6, ___tag1, ## __VA_ARGS__)
#define __MUI_Request_WB(___base, ___par1, ___par2, ___par3, ___par4, ___par5, ___par6, ___tag1, ...) \
	({IPTR _message[] = { (IPTR) ___tag1, ## __VA_ARGS__ }; __MUI_RequestA_WB((___base), (___par1), (___par2), (___par3), (___par4), (___par5), (___par6), (APTR) _message); })
#endif /* !NO_INLINE_VARARGS */

#define MUI_AllocAslRequest(___par1, ___last) __MUI_AllocAslRequest_WB(MUIMASTER_BASE_NAME, ___par1, ___last)
#define __MUI_AllocAslRequest_WB(___base, ___par1, ___last) \
	AROS_LC2(APTR, MUI_AllocAslRequest, \
	AROS_LCA(unsigned long, (___par1), D0), \
	AROS_LCA(struct TagItem *, (___last), A0), \
	struct Library *, (___base), 8, Muimaster)

#ifndef NO_INLINE_STDARG
#define MUI_AllocAslRequestTags(___par1, ___last, ...) __MUI_AllocAslRequestTags_WB(MUIMASTER_BASE_NAME, ___par1, ___last, ## __VA_ARGS__)
#define __MUI_AllocAslRequestTags_WB(___base, ___par1, ___last, ...) \
	({IPTR _tags[] = { (IPTR) ___last, ## __VA_ARGS__ }; __MUI_AllocAslRequest_WB((___base), (___par1), (struct TagItem *) _tags); })
#endif /* !NO_INLINE_STDARG */

#define MUI_AslRequest(___par1, ___last) __MUI_AslRequest_WB(MUIMASTER_BASE_NAME, ___par1, ___last)
#define __MUI_AslRequest_WB(___base, ___par1, ___last) \
	AROS_LC2(BOOL, MUI_AslRequest, \
	AROS_LCA(APTR, (___par1), A0), \
	AROS_LCA(struct TagItem *, (___last), A1), \
	struct Library *, (___base), 9, Muimaster)

#ifndef NO_INLINE_STDARG
#define MUI_AslRequestTags(___par1, ___last, ...) __MUI_AslRequestTags_WB(MUIMASTER_BASE_NAME, ___par1, ___last, ## __VA_ARGS__)
#define __MUI_AslRequestTags_WB(___base, ___par1, ___last, ...) \
	({IPTR _tags[] = { (IPTR) ___last, ## __VA_ARGS__ }; __MUI_AslRequest_WB((___base), (___par1), (struct TagItem *) _tags); })
#endif /* !NO_INLINE_STDARG */

#define MUI_FreeAslRequest(___last) __MUI_FreeAslRequest_WB(MUIMASTER_BASE_NAME, ___last)
#define __MUI_FreeAslRequest_WB(___base, ___last) \
	AROS_LC1NR(VOID, MUI_FreeAslRequest, \
	AROS_LCA(APTR, (___last), A0), \
	struct Library *, (___base), 10, Muimaster)

#define MUI_Error() __MUI_Error_WB(MUIMASTER_BASE_NAME)
#define __MUI_Error_WB(___base) \
	AROS_LC0(LONG, MUI_Error, \
	struct Library *, (___base), 11, Muimaster)

#define MUI_SetError(___last) __MUI_SetError_WB(MUIMASTER_BASE_NAME, ___last)
#define __MUI_SetError_WB(___base, ___last) \
	AROS_LC1(LONG, MUI_SetError, \
	AROS_LCA(LONG, (___last), D0), \
	struct Library *, (___base), 12, Muimaster)

#define MUI_GetClass(___last) __MUI_GetClass_WB(MUIMASTER_BASE_NAME, ___last)
#define __MUI_GetClass_WB(___base, ___last) \
	AROS_LC1(struct IClass *, MUI_GetClass, \
	AROS_LCA(CONST_STRPTR, (___last), A0), \
	struct Library *, (___base), 13, Muimaster)

#define MUI_FreeClass(___last) __MUI_FreeClass_WB(MUIMASTER_BASE_NAME, ___last)
#define __MUI_FreeClass_WB(___base, ___last) \
	AROS_LC1NR(VOID, MUI_FreeClass, \
	AROS_LCA(struct IClass *, (___last), A0), \
	struct Library *, (___base), 14, Muimaster)

#define MUI_RequestIDCMP(___par1, ___last) __MUI_RequestIDCMP_WB(MUIMASTER_BASE_NAME, ___par1, ___last)
#define __MUI_RequestIDCMP_WB(___base, ___par1, ___last) \
	AROS_LC2NR(VOID, MUI_RequestIDCMP, \
	AROS_LCA(Object *, (___par1), A0), \
	AROS_LCA(ULONG, (___last), D0), \
	struct Library *, (___base), 15, Muimaster)

#define MUI_RejectIDCMP(___par1, ___last) __MUI_RejectIDCMP_WB(MUIMASTER_BASE_NAME, ___par1, ___last)
#define __MUI_RejectIDCMP_WB(___base, ___par1, ___last) \
	AROS_LC2NR(VOID, MUI_RejectIDCMP, \
	AROS_LCA(Object *, (___par1), A0), \
	AROS_LCA(ULONG, (___last), D0), \
	struct Library *, (___base), 16, Muimaster)

#define MUI_Redraw(___par1, ___last) __MUI_Redraw_WB(MUIMASTER_BASE_NAME, ___par1, ___last)
#define __MUI_Redraw_WB(___base, ___par1, ___last) \
	AROS_LC2NR(VOID, MUI_Redraw, \
	AROS_LCA(Object *, (___par1), A0), \
	AROS_LCA(ULONG, (___last), D0), \
	struct Library *, (___base), 17, Muimaster)

#define MUI_CreateCustomClass(___par1, ___par2, ___par3, ___par4, ___last) __MUI_CreateCustomClass_WB(MUIMASTER_BASE_NAME, ___par1, ___par2, ___par3, ___par4, ___last)
#define __MUI_CreateCustomClass_WB(___base, ___par1, ___par2, ___par3, ___par4, ___last) \
	AROS_LC5(struct MUI_CustomClass *, MUI_CreateCustomClass, \
	AROS_LCA(struct Library *, (___par1), A0), \
	AROS_LCA(CONST_STRPTR, (___par2), A1), \
	AROS_LCA(struct MUI_CustomClass *, (___par3), A2), \
	AROS_LCA(int, (___par4), D0), \
	AROS_LCA(APTR, (___last), A3), \
	struct Library *, (___base), 18, Muimaster)

#define MUI_DeleteCustomClass(___last) __MUI_DeleteCustomClass_WB(MUIMASTER_BASE_NAME, ___last)
#define __MUI_DeleteCustomClass_WB(___base, ___last) \
	AROS_LC1(BOOL, MUI_DeleteCustomClass, \
	AROS_LCA(struct MUI_CustomClass *, (___last), A0), \
	struct Library *, (___base), 19, Muimaster)

#define MUI_MakeObjectA(___par1, ___last) __MUI_MakeObjectA_WB(MUIMASTER_BASE_NAME, ___par1, ___last)
#define __MUI_MakeObjectA_WB(___base, ___par1, ___last) \
	AROS_LC2(Object *, MUI_MakeObjectA, \
	AROS_LCA(LONG, (___par1), D0), \
	AROS_LCA(ULONG *, (___last), A0), \
	struct Library *, (___base), 20, Muimaster)

#ifndef NO_INLINE_VARARGS
#define MUI_MakeObject(___par1, ___tag1, ...) __MUI_MakeObject_WB(MUIMASTER_BASE_NAME, ___par1, ___tag1, ## __VA_ARGS__)
#define __MUI_MakeObject_WB(___base, ___par1, ___tag1, ...) \
	({IPTR _message[] = { (IPTR) ___tag1, ## __VA_ARGS__ }; __MUI_MakeObjectA_WB((___base), (___par1), (ULONG *) _message); })
#endif /* !NO_INLINE_VARARGS */

#define MUI_Layout(___par1, ___par2, ___par3, ___par4, ___par5, ___last) __MUI_Layout_WB(MUIMASTER_BASE_NAME, ___par1, ___par2, ___par3, ___par4, ___par5, ___last)
#define __MUI_Layout_WB(___base, ___par1, ___par2, ___par3, ___par4, ___par5, ___last) \
	AROS_LC6(BOOL, MUI_Layout, \
	AROS_LCA(Object *, (___par1), A0), \
	AROS_LCA(LONG, (___par2), D0), \
	AROS_LCA(LONG, (___par3), D1), \
	AROS_LCA(LONG, (___par4), D2), \
	AROS_LCA(LONG, (___par5), D3), \
	AROS_LCA(ULONG, (___last), D4), \
	struct Library *, (___base), 21, Muimaster)

#define MUI_ObtainPen(___par1, ___par2, ___last) __MUI_ObtainPen_WB(MUIMASTER_BASE_NAME, ___par1, ___par2, ___last)
#define __MUI_ObtainPen_WB(___base, ___par1, ___par2, ___last) \
	AROS_LC3(LONG, MUI_ObtainPen, \
	AROS_LCA(struct MUI_RenderInfo *, (___par1), A0), \
	AROS_LCA(struct MUI_PenSpec *, (___par2), A1), \
	AROS_LCA(ULONG, (___last), D0), \
	struct Library *, (___base), 26, Muimaster)

#define MUI_ReleasePen(___par1, ___last) __MUI_ReleasePen_WB(MUIMASTER_BASE_NAME, ___par1, ___last)
#define __MUI_ReleasePen_WB(___base, ___par1, ___last) \
	AROS_LC2NR(VOID, MUI_ReleasePen, \
	AROS_LCA(struct MUI_RenderInfo *, (___par1), A0), \
	AROS_LCA(LONG, (___last), D0), \
	struct Library *, (___base), 27, Muimaster)

#define MUI_AddClipping(___par1, ___par2, ___par3, ___par4, ___last) __MUI_AddClipping_WB(MUIMASTER_BASE_NAME, ___par1, ___par2, ___par3, ___par4, ___last)
#define __MUI_AddClipping_WB(___base, ___par1, ___par2, ___par3, ___par4, ___last) \
	AROS_LC5(APTR, MUI_AddClipping, \
	AROS_LCA(struct MUI_RenderInfo *, (___par1), A0), \
	AROS_LCA(WORD, (___par2), D0), \
	AROS_LCA(WORD, (___par3), D1), \
	AROS_LCA(WORD, (___par4), D2), \
	AROS_LCA(WORD, (___last), D3), \
	struct Library *, (___base), 28, Muimaster)

#define MUI_RemoveClipping(___par1, ___last) __MUI_RemoveClipping_WB(MUIMASTER_BASE_NAME, ___par1, ___last)
#define __MUI_RemoveClipping_WB(___base, ___par1, ___last) \
	AROS_LC2NR(VOID, MUI_RemoveClipping, \
	AROS_LCA(struct MUI_RenderInfo *, (___par1), A0), \
	AROS_LCA(APTR, (___last), A1), \
	struct Library *, (___base), 29, Muimaster)

#define MUI_AddClipRegion(___par1, ___last) __MUI_AddClipRegion_WB(MUIMASTER_BASE_NAME, ___par1, ___last)
#define __MUI_AddClipRegion_WB(___base, ___par1, ___last) \
	AROS_LC2(APTR, MUI_AddClipRegion, \
	AROS_LCA(struct MUI_RenderInfo *, (___par1), A0), \
	AROS_LCA(struct Region *, (___last), A1), \
	struct Library *, (___base), 30, Muimaster)

#define MUI_RemoveClipRegion(___par1, ___last) __MUI_RemoveClipRegion_WB(MUIMASTER_BASE_NAME, ___par1, ___last)
#define __MUI_RemoveClipRegion_WB(___base, ___par1, ___last) \
	AROS_LC2NR(VOID, MUI_RemoveClipRegion, \
	AROS_LCA(struct MUI_RenderInfo *, (___par1), A0), \
	AROS_LCA(APTR, (___last), A1), \
	struct Library *, (___base), 31, Muimaster)

#define MUI_BeginRefresh(___par1, ___last) __MUI_BeginRefresh_WB(MUIMASTER_BASE_NAME, ___par1, ___last)
#define __MUI_BeginRefresh_WB(___base, ___par1, ___last) \
	AROS_LC2(BOOL, MUI_BeginRefresh, \
	AROS_LCA(struct MUI_RenderInfo *, (___par1), A0), \
	AROS_LCA(ULONG, (___last), D0), \
	struct Library *, (___base), 32, Muimaster)

#define MUI_EndRefresh(___par1, ___last) __MUI_EndRefresh_WB(MUIMASTER_BASE_NAME, ___par1, ___last)
#define __MUI_EndRefresh_WB(___base, ___par1, ___last) \
	AROS_LC2NR(VOID, MUI_EndRefresh, \
	AROS_LCA(struct MUI_RenderInfo *, (___par1), A0), \
	AROS_LCA(ULONG, (___last), D0), \
	struct Library *, (___base), 33, Muimaster)

#endif /* !_INLINE_MUIMASTER_H */
