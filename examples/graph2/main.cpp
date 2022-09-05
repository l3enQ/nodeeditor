#include <QtNodes/ConnectionStyle>
#include <QtNodes/GraphicsView>
#include <QtNodes/BasicGraphicsScene>
#include <QtNodes/StyleCollection>

#include <QtNodes/NodeDelegateModelRegistry>
#include <QtNodes/BehaviorTreeGraphModel>

#include <QtWidgets/QApplication>
#include <QAction>
#include <QScreen>
#include <QLabel>
#include <QMenuBar>
#include <QBoxLayout>
#include <QWidgetAction>


#include "actionnodedatamodel.h"
#include "controlnodedatamodel.h"
#include "decoratornodedatamodel.h"

#include "qstandarditemmodel.h"
#include "widgets/loadedtreeswidget.h"
#include "widgets/modelswidget.h"


using QtNodes::ConnectionStyle;
using QtNodes::GraphicsView;
using QtNodes::BasicGraphicsScene;
using QtNodes::NodeRole;
using QtNodes::NodeDelegateModelRegistry;
using QtNodes::StyleCollection;

using QtNodes::BehaviorTreeGraphModel;

static std::shared_ptr<NodeDelegateModelRegistry>
registerDataModels()
{
  auto ret = std::make_shared<NodeDelegateModelRegistry>();
  ret->registerModel<ActionNodeDataModel>("Nodes");
  ret->registerModel<ControlNodeDataModel>("Nodes");
  ret->registerModel<DecoratorNodeDataModel>("Nodes");

  return ret;
}

int
main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  std::shared_ptr<NodeDelegateModelRegistry> registry = registerDataModels();

  BehaviorTreeGraphModel graphModel(registry);

  // Initialize and connect some nodes.
  {
      NodeId const id1 = graphModel.addNode("Control");
      if (id1 != InvalidNodeId)
      {
          graphModel.setNodeData(id1,
                                 NodeRole::Position,
                                 QPointF(0, 0));
      }

      NodeId const id2 = graphModel.addNode("Control");
      if (id2 != InvalidNodeId)
      {
          graphModel.setNodeData(id2,
                                 NodeRole::Position,
                                 QPointF(200, 0));
      }
      graphModel.addConnection(ConnectionId{id1, 0, id2, 0});

      NodeId const idd1 = graphModel.addNode("Decorator");
      if (idd1 != InvalidNodeId)
      {
          graphModel.setNodeData(idd1,
                                 NodeRole::Position,
                                 QPointF(400, 0));
      }
      NodeId const idd2 = graphModel.addNode("Decorator");
      if (idd2 != InvalidNodeId)
      {
          graphModel.setNodeData(idd2,
                                 NodeRole::Position,
                                 QPointF(400, 200));
      }
      graphModel.addConnection(ConnectionId{id2, 0, idd1, 0});
      graphModel.addConnection(ConnectionId{id2, 0, idd2, 0});

      NodeId const ida1 = graphModel.addNode("Action");
      if (ida1 != InvalidNodeId)
      {
          graphModel.setNodeData(ida1,
                                 NodeRole::Position,
                                 QPointF(600, 0));
      }
      NodeId const ida2 = graphModel.addNode("Action");
      if (ida2 != InvalidNodeId)
      {
          graphModel.setNodeData(ida2,
                                 NodeRole::Position,
                                 QPointF(600, 200));
      }
      NodeId const ida3 = graphModel.addNode("Action");
      if (ida3 != InvalidNodeId)
      {
          graphModel.setNodeData(ida3,
                                 NodeRole::Position,
                                 QPointF(400, 400));
      }
      graphModel.addConnection(ConnectionId{idd1, 0, ida1, 0});
      graphModel.addConnection(ConnectionId{idd2, 0, ida2, 0});
      graphModel.addConnection(ConnectionId{id2,  0, ida3, 0});
  }

  auto model = new QStandardItemModel(&app);
  std::map<QString, QStandardItem *> _tree_view_category_items;

  for (const QString& category : {"Action", "Condition",
       "Control", "Decorator", "SubTree" } )
  {
      auto item = new QStandardItem(category);
      model->appendRow(item);
      QFont font = item->data(Qt::FontRole).value<QFont>();
      font.setBold(true);
      font.setPointSize(11);
      item->setData(font, Qt::FontRole);
      item->setFlags( item->flags() ^ Qt::ItemIsDragEnabled );
      item->setFlags( item->flags() ^ Qt::ItemIsSelectable );
      _tree_view_category_items[ category ] = item;
  }

  for (const auto &it : _tree_view_category_items) {
      auto item = new QStandardItem(it.first);
      it.second->appendRow(item);
      QFont font = item->data(Qt::FontRole).value<QFont>();
      font.setBold(false);
      font.setPointSize(10);
      item->setData(font, Qt::FontRole);
  }

  auto treesModel = new QStandardItemModel(&app);
  std::map<QString, QStandardItem *> _tree_view_tree_files;

  for (const QString &file : {"File1", "File2",
       "File3" } )
  {
      auto item = new QStandardItem(file);
      treesModel->appendRow(item);
      QFont font = item->data(Qt::FontRole).value<QFont>();
      font.setBold(false);
      font.setPointSize(11);
      item->setData(font, Qt::FontRole);
      item->setFlags( item->flags() ^ Qt::ItemIsDragEnabled );
      item->setFlags( item->flags() ^ Qt::ItemIsSelectable );
      _tree_view_tree_files[ file ] = item;
  }

  for (const auto &it : _tree_view_tree_files) {
      auto item = new QStandardItem(it.first);
      it.second->appendRow(item);
      QFont font = item->data(Qt::FontRole).value<QFont>();
      font.setBold(false);
      font.setPointSize(10);
      item->setData(font, Qt::FontRole);
  }


  QWidget mainWidget;

  auto menuBar = new QMenuBar();
  auto saveAction = menuBar->addAction("Save..");
  auto loadAction = menuBar->addAction("Load..");

  QVBoxLayout* l = new QVBoxLayout(&mainWidget);
  l->setContentsMargins(0, 0, 0, 0);
  l->setSpacing(0);

  l->addWidget(menuBar);

  QHBoxLayout* lh = new QHBoxLayout();
  lh->setContentsMargins(0, 0, 0, 0);
  lh->setSpacing(0);
  l->addLayout(lh);

  QVBoxLayout* lv = new QVBoxLayout();
  lh->setContentsMargins(0, 0, 0, 0);
  lh->setSpacing(0);
  lh->addLayout(lv);

  lv->addWidget(new ModelsWidget("Trees", treesModel));
  lv->addWidget(new ModelsWidget("Models", model));

  auto scene = new BasicGraphicsScene(graphModel);

  GraphicsView view(scene);

  // Setup context menu for creating new nodes.
  view.setContextMenuPolicy(Qt::ActionsContextMenu);

  for (auto const& cat : registry->categories())
  {
      auto sep = new QAction();
      sep->setSeparator(true);
      view.insertAction(view.actions().front(), sep);

      for (auto const& assoc : registry->registeredModelsCategoryAssociation())
      {
          if (assoc.second != cat)
              continue;

          QString name = assoc.first;
          QAction *createNodeAction = new QAction(name, &view);

          QObject::connect(createNodeAction, &QAction::triggered,
                           [&, name]()
          {
              // Mouse position in scene coordinates.
              QPointF posView =
                      view.mapToScene(view.mapFromGlobal(QCursor::pos()));

              NodeId const newId = graphModel.addNode(name);
              if (newId != InvalidNodeId)
              {
                  graphModel.setNodeData(newId,
                                         NodeRole::Position,
                                         posView);
              }
          });

          view.insertAction(view.actions().front(), createNodeAction);
      }
      QLabel* label = new QLabel(QString("<b>%0</b>").arg(cat));
      label->setAlignment(Qt::AlignCenter);

      QWidgetAction *a = new QWidgetAction(nullptr);
      a->setDefaultWidget(label);
      view.insertAction(view.actions().front(), a);
  }

  lh->addWidget(&view);

  mainWidget.setWindowTitle("Simple Node Graph");
  mainWidget.resize(800, 600);
  // Center window.
  mainWidget.move(QApplication::primaryScreen()->availableGeometry().center() - mainWidget.rect().center());
  mainWidget.showNormal();

  return app.exec();
}

