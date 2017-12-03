#pragma once


namespace XE {

	enum EUSID
	{
		Gizmo,

		//renderer
		SceneHierarchy,
		NodeProperties,

		//mainthread
		entities,
		physicObjects
	};

	class IEditorUIState
	{
	public :
		virtual void render() = 0;

		int ID;
	};
}