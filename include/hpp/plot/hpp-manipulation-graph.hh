#ifndef HPP_PLOT_HPP_MANIPULATION_GRAPH_HH
#define HPP_PLOT_HPP_MANIPULATION_GRAPH_HH

#include <QAction>

#include <hpp/corbaserver/manipulation/client.hh>

#include <hpp/plot/graph-widget.hh>

namespace hpp {
  namespace corbaServer {
    namespace manipulation {
      class Client;
    }
  }
  namespace plot {
    class GraphAction : public QAction
    {
      Q_OBJECT

    public:
      GraphAction (QWidget* parent = NULL);
      hpp::ID id_;

    signals:
      void activated (hpp::ID id);

    private slots:
      void transferSignal ();
    };

    class HppManipulationGraphWidget : public GraphWidget
    {
      Q_OBJECT

    public:
      HppManipulationGraphWidget (corbaServer::manipulation::Client* hpp_, QWidget* parent);

      ~HppManipulationGraphWidget ();

      void addNodeContextMenuAction (GraphAction* action);
      void addEdgeContextMenuAction (GraphAction* action);

      void client (corbaServer::manipulation::Client* hpp);

    protected:
      void fillScene ();

    public slots:
      void updateStatistics ();

    protected slots:
      virtual void nodeContextMenu(QGVNode* node);
      virtual void nodeDoubleClick(QGVNode* node);
      virtual void edgeContextMenu(QGVEdge* edge);
      virtual void edgeDoubleClick(QGVNode* edge);

      void selectionChanged ();

    private slots:
      void startStopUpdateStats (bool start);

    private:
      corbaServer::manipulation::Client* manip_;

      struct NodeInfo {
        ::hpp::ID id;
        QString constraintStr;

        ::hpp::ConfigProjStat_var configStat, pathStat;
        NodeInfo ();
      };
      struct EdgeInfo {
        ::hpp::ID id;
        QString constraintStr;

        ::hpp::ConfigProjStat_var configStat, pathStat;
        EdgeInfo ();
      };

      QList <GraphAction*> nodeContextMenuActions_;
      QList <GraphAction*> edgeContextMenuActions_;
      QMap <QGVNode*, NodeInfo> nodeInfos_;
      QMap <QGVEdge*, EdgeInfo> edgeInfos_;

      QTimer* updateStatsTimer_;
    };
  }
}

#endif // HPP_PLOT_HPP_MANIPULATION_GRAPH_HH
