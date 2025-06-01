bl_info = {
    "name": "Export JSON for polytool",
    "description": "Exports all faces in the scene as tris in JSON format",
    "category": "Import-Export",
    "blender": (2, 99, 0)
}

import bpy
import bmesh
import json

# ExportHelper is a helper class, defines filename and
# invoke() function which calls the file selector.
from bpy_extras.io_utils import ExportHelper
from bpy.props import StringProperty, BoolProperty, EnumProperty
from bpy.types import Operator

class ExportSomeData(Operator, ExportHelper):
    bl_idname = "export_test.poly_json_export"  # important since its how bpy.ops.import_test.some_data is constructed
    bl_label = "Export JSON (polys)"

    # ExportHelper mixin class uses this
    filename_ext = ".json"

    filter_glob: StringProperty(
        default="*.json",
        options={'HIDDEN'},
        maxlen=255,  # Max internal buffer length, longer would be clamped.
    )
    
    def execute(self, context):
        #print("running write_some_data...")
        #f = open(filepath, 'w', encoding='utf-8')
        #f.write("Hello World %s" % use_some_setting)
        #f.close()
        
        #for o in context.scene.objects:
        #    print(o)
        
        if(context.mode == 'OBJECT'):
            obj = context.active_object
            
            exportable_polys = []
            
            for f in obj.data.polygons:
                face_verts = []
                face_material = obj.material_slots[f.material_index].name
                
                for v_index in f.vertices:
                    face_verts.append([obj.data.vertices[v_index].co.x, obj.data.vertices[v_index].co.y, obj.data.vertices[v_index].co.z])
                exportable_polys.append({
                    "material": face_material,
                    "poly": face_verts
                })
            
            f = open(self.filepath, 'w', encoding='utf-8')
            f.write(json.dumps(exportable_polys, indent=2))
            f.close()
        
        return {'FINISHED'}


# Only needed if you want to add into a dynamic menu
def menu_func_export(self, context):
    self.layout.operator(ExportSomeData.bl_idname, text="Polytool JSON (.json)")

# Register and add to the "file selector" menu (required to use F3 search "Text Export Operator" for quick access)
def register():
    bpy.utils.register_class(ExportSomeData)
    bpy.types.TOPBAR_MT_file_export.append(menu_func_export)


def unregister():
    bpy.utils.unregister_class(ExportSomeData)
    bpy.types.TOPBAR_MT_file_export.remove(menu_func_export)


if __name__ == "__main__":
    register()

    # test call
    #bpy.ops.export_test.some_data('INVOKE_DEFAULT')
