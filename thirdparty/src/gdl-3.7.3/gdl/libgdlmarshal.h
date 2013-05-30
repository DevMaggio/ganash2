
#ifndef __gdl_marshal_MARSHAL_H__
#define __gdl_marshal_MARSHAL_H__

#include	<glib-object.h>

G_BEGIN_DECLS

/* VOID:VOID (/home/seb-mint-13/Programmation/Anjuta/gdl/gdl/libgdlmarshal.list:1) */
#define gdl_marshal_VOID__VOID	g_cclosure_marshal_VOID__VOID

/* VOID:ENUM (/home/seb-mint-13/Programmation/Anjuta/gdl/gdl/libgdlmarshal.list:2) */
#define gdl_marshal_VOID__ENUM	g_cclosure_marshal_VOID__ENUM

/* VOID:UINT,UINT (/home/seb-mint-13/Programmation/Anjuta/gdl/gdl/libgdlmarshal.list:3) */
extern void gdl_marshal_VOID__UINT_UINT (GClosure     *closure,
                                         GValue       *return_value,
                                         guint         n_param_values,
                                         const GValue *param_values,
                                         gpointer      invocation_hint,
                                         gpointer      marshal_data);

/* VOID:BOOLEAN (/home/seb-mint-13/Programmation/Anjuta/gdl/gdl/libgdlmarshal.list:4) */
#define gdl_marshal_VOID__BOOLEAN	g_cclosure_marshal_VOID__BOOLEAN

/* VOID:OBJECT,INT,INT (/home/seb-mint-13/Programmation/Anjuta/gdl/gdl/libgdlmarshal.list:5) */
extern void gdl_marshal_VOID__OBJECT_INT_INT (GClosure     *closure,
                                              GValue       *return_value,
                                              guint         n_param_values,
                                              const GValue *param_values,
                                              gpointer      invocation_hint,
                                              gpointer      marshal_data);

/* VOID:OBJECT,ENUM,BOXED (/home/seb-mint-13/Programmation/Anjuta/gdl/gdl/libgdlmarshal.list:6) */
extern void gdl_marshal_VOID__OBJECT_ENUM_BOXED (GClosure     *closure,
                                                 GValue       *return_value,
                                                 guint         n_param_values,
                                                 const GValue *param_values,
                                                 gpointer      invocation_hint,
                                                 gpointer      marshal_data);

/* VOID:BOXED (/home/seb-mint-13/Programmation/Anjuta/gdl/gdl/libgdlmarshal.list:7) */
#define gdl_marshal_VOID__BOXED	g_cclosure_marshal_VOID__BOXED

G_END_DECLS

#endif /* __gdl_marshal_MARSHAL_H__ */

