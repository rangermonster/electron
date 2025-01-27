// Copyright (c) 2014 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef SHELL_BROWSER_API_ATOM_API_TRAY_H_
#define SHELL_BROWSER_API_ATOM_API_TRAY_H_

#include <memory>
#include <string>
#include <vector>

#include "native_mate/handle.h"
#include "shell/browser/api/trackable_object.h"
#include "shell/browser/ui/tray_icon.h"
#include "shell/browser/ui/tray_icon_observer.h"

namespace gfx {
class Image;
}

namespace mate {
class Arguments;
class Dictionary;
}  // namespace mate

namespace electron {

class TrayIcon;

namespace api {

class Menu;
class NativeImage;

class Tray : public mate::TrackableObject<Tray>, public TrayIconObserver {
 public:
  static mate::WrappableBase* New(mate::Handle<NativeImage> image,
                                  mate::Arguments* args);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

 protected:
  Tray(v8::Isolate* isolate,
       v8::Local<v8::Object> wrapper,
       mate::Handle<NativeImage> image);
  ~Tray() override;

  // TrayIconObserver:
  void OnClicked(const gfx::Rect& bounds,
                 const gfx::Point& location,
                 int modifiers) override;
  void OnDoubleClicked(const gfx::Rect& bounds, int modifiers) override;
  void OnRightClicked(const gfx::Rect& bounds, int modifiers) override;
  void OnBalloonShow() override;
  void OnBalloonClicked() override;
  void OnBalloonClosed() override;
  void OnDrop() override;
  void OnDropFiles(const std::vector<std::string>& files) override;
  void OnDropText(const std::string& text) override;
  void OnDragEntered() override;
  void OnDragExited() override;
  void OnDragEnded() override;
  void OnMouseEntered(const gfx::Point& location, int modifiers) override;
  void OnMouseExited(const gfx::Point& location, int modifiers) override;
  void OnMouseMoved(const gfx::Point& location, int modifiers) override;

  void SetImage(v8::Isolate* isolate, mate::Handle<NativeImage> image);
  void SetPressedImage(v8::Isolate* isolate, mate::Handle<NativeImage> image);
  void SetToolTip(const std::string& tool_tip);
  void SetTitle(const std::string& title);
  std::string GetTitle();
  void SetIgnoreDoubleClickEvents(bool ignore);
  bool GetIgnoreDoubleClickEvents();
  void DisplayBalloon(mate::Arguments* args, const mate::Dictionary& options);
  void RemoveBalloon();
  void PopUpContextMenu(mate::Arguments* args);
  void SetContextMenu(v8::Isolate* isolate, mate::Handle<Menu> menu);
  gfx::Rect GetBounds();

 private:
  v8::Global<v8::Object> menu_;
  std::unique_ptr<TrayIcon> tray_icon_;

  DISALLOW_COPY_AND_ASSIGN(Tray);
};

}  // namespace api

}  // namespace electron

#endif  // SHELL_BROWSER_API_ATOM_API_TRAY_H_
